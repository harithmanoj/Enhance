/** ***************************************************************************
	\file QueuedProcess.enh.h

	\brief The file to declare class QueuedProcess

	Created 11 April 2020

	This file is part of project Enhance C++ Libraries.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.


******************************************************************************/

#ifndef QUEUED_PROCESS_ENH_H

#define QUEUED_PROCESS_ENH_H						QueuedProcess.enh.h

#include "error_base.enh.h"

#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <new>

namespace enh
{

	/**
		\brief The structure to encapsulate an instruction passed to the
		queue as 3 components.
	*/
	template< class Msg, class Lower, class Upper>
	struct GenInstruct
	{
		Msg op;
		Lower lParam;
		Upper uParam;
	};

	/**
		\brief The structure to encapsulate an instruction passed to the
		queue as 4 components.
	*/
	template< class Msg, class Lower, class Upper, class Fourth>
	struct QuadInstruct
	{
		Msg op;
		Lower lParam;
		Upper uParam;
		Fourth last;
	};


	/**
		\brief The type to add as place-holder in passing template arguments
		to templates which may not require all types to be valid.
	*/
	class Blank_t {};

	/**
		\brief The class to implement a structure which executes instructions
		concurently after fetching them through a queue for final use
		including debug calls.


		hasErrorHandlers        = false;\n

		The function RegisterProc must be called to setup the processing function
		before starting the queue process.\n\n

		<h3>Template arguments</h3>
		-#  <code>class Instruct</code> : The type to store the instruction.\n

		
		<h3> How To Use </h3>

		- Create a structure that contains information to be sequentially 
		processed. Let it be `struct info`. You can use structures 
		`gen_instruct` and `quad_instruct` to merge different types easily.
		The type must be copy-constructible. Let it be `info`.

		- Create a Function of type QueuedProcess::processing_method returns 
		`tristate`, takes `info` as argument. The function should return 
		something other than tristate::GOOD if a fatal error occurs. Let it 
		be `proc`.

		- Create object of `queued_process<info>`, construct by passing `proc`
		 or default construct then call `Register(proc)`.

		- Call `start_queue_process` to start waiting on messages.

		- Call `postMessage` and pass the message to add message to queue.

		- Call `stopQueue` to stop processing.

		- Call `WaitForQueueStop` to wait till queued execution thread stops.
		Will only stop after executing full queue unless function returns 
		error.


		<h3>Example</h3>
		
		\include{lineno} queued_process_ex.cpp

	*/
	template< class Instruct>
	class QueuedProcess 
	{
	public:

		/**
			\brief The type of object to be processed
		*/
		using info_type = Instruct;

		/**
			\brief The function type that processes the infomation passed.
		*/
		using processing_method = std::function<tristate(info_type)>;

	private:

		/**
			\brief The synchronising mutex for Queue.
		*/
		std::mutex mtxQueue;

		/**
			\brief The Queue to pass instruction from main to instruction processor.
		*/
		std::queue<info_type> QueuedMessage;

		/**
			\brief The object to notify update to queue.
		*/
		std::condition_variable cvQueue;

		/**
			\brief The bool value which indicates whether queue has been
			updated to avoid false wake-ups.
		*/
		std::atomic<bool> isUpdated;

		/**
			\brief The bool variable which signals the instruction processing
			function to stop and exit after emptying the queue.
		*/
		std::atomic<bool> QueueStop;

		/**
			\brief sets to true if Queued instruction processor is active.
		*/
		std::atomic<bool> isQueueActive;

		/**
			\brief The function which processes the instruction then.
		*/
		processing_method msgProc;

		/**
			\brief The thread handle for the queue process.
		*/
		std::thread queue_thread;



		/**
			\brief loops and executes tasks pushed into message queue until
			EXIT_QUEUE is pushed into the queue.


			<h3>Return</h3>
			Returns tristate::ERROR if any msg_switch fails.\n
			Returns tristate::PREV_ERROR if error was flagged in any previous
			function calls.\n

		*/
		tristate queue_exec_process() noexcept
		{
			O1_LIB_LOG_LINE;
			if (!msgProc)
				return tristate::ERROR;
			O1_LIB_LOG_LINE;
			while (!(QueueStop.load()))
			{
				O3_LIB_LOG_LINE;
				while (!(isUpdated.load()))
				{
					std::unique_lock<std::mutex> lock(mtxQueue);
					cvQueue.wait(lock);
					bool empty = QueuedMessage.empty();
					lock.unlock();
					if (!(isUpdated.load()) && QueueStop.load() && empty)
						return (tristate::GOOD);

				}
				isUpdated = false;
				bool stopNow = false;
				{
					std::lock_guard<std::mutex> lock(mtxQueue);
					stopNow = QueuedMessage.empty() || QueueStop.load();
				}
				while (!stopNow)
				{
					O3_LIB_LOG_LINE;
					mtxQueue.lock();
					info_type front = QueuedMessage.front();
					QueuedMessage.pop();
					mtxQueue.unlock();
					tristate ret = msgProc(front);
					if (!ret)
						return (tristate::ERROR);
					std::lock_guard<std::mutex> temp_lock(mtxQueue);
					stopNow = QueuedMessage.empty() || QueueStop.load();
				}

			}
			O4_LIB_LOG_LINE;
			return (tristate::GOOD);
		}

	public:

		

		/**
			\brief The default constructor.
		*/
		QueuedProcess() noexcept : queue_thread()
		{
			isUpdated = false;
			QueueStop = false;
			isQueueActive = false;
		}

		/**
			\brief Registers the processing method while constructing.
		*/
		explicit QueuedProcess(
			processing_method msg /**< : <i>in</i> : The procedure.*/
		) noexcept : queue_thread()
		{
			isUpdated = false;
			QueueStop = false;
			isQueueActive = false;
			msgProc = msg;
		}

		QueuedProcess(const QueuedProcess&) = delete;

		QueuedProcess(QueuedProcess&&) = delete;

		QueuedProcess& operator = (QueuedProcess&&) = delete;

		QueuedProcess& operator = (const QueuedProcess&) = delete;

		/**
			\brief The Function to set a function as the instruction processor.
		*/
		inline void RegisterProc(
			processing_method in /**< : <i>in</i> : The procedure.*/
		) noexcept
		{
			msgProc = in;
		}

		/**
			\brief starts the function queue_process in another thread.

			<h3>Return</h3>
			Returns tristate::ERROR if no procedure was set, or queue is
			already running or if thread allocation failed.\n
			Returns tristate::PREV_ERROR if error was flagged in any previous
			function calls.\n
		*/
		tristate start_queue_process() noexcept
		{
			O3_LIB_LOG_LINE;
			if (!msgProc)
				return tristate::ERROR;
			if (isQueueRunning())
				return tristate::ERROR;
			O2_LIB_LOG_LINE;
			QueueStop = false;
			queue_thread = std::thread(
				&QueuedProcess::queue_exec_process, this);
			isQueueActive = true;
			O2_LIB_LOG_LINE;
			return (tristate::GOOD);
		}

		/**
			\brief check if queue is updated.

			<h3>Return</h3>
			Returns isUpdated.\n

		*/
		inline bool isQueueUpdated() noexcept
		{
			return isUpdated.load();
		}

		/**
			\brief The function post a message onto the queue.
		*/
		inline void postMessage(
			info_type Message /**< : <i>in</i> : Message need to be pushed.*/
		)
		{
			{
				std::lock_guard<std::mutex> lock(mtxQueue);
				QueuedMessage.push(Message);
				isUpdated = true;
			}
			cvQueue.notify_all();
			return;
		}


		/**
			\brief The function to signal the queue to stop processing after
			emptying the queue.
		*/
		inline void stopQueue() noexcept
		{
			QueueStop = true;
			cvQueue.notify_all();
		}


		/**
			\brief Checks if Queue is running.

		  <h3>Return</h3>
		  true if queue is running.\n

		*/
		inline bool isQueueRunning() noexcept { return isQueueActive.load(); };

		/**
			\brief Waits till Queued process stops execution. Then empties queue.
		*/
		inline void WaitForQueueStop() noexcept
		{
			if (queue_thread.joinable() || isQueueRunning() )
			{
				O3_LIB_LOG_LINE;
				queue_thread.join();
				O4_LIB_LOG_LINE;
				isQueueActive = false;
				QueueStop = false;
				std::lock_guard<std::mutex> lock(mtxQueue);
				QueuedMessage = std::queue<Instruct>();
			}

		}

		/**
			\brief Waits till Queue is Empty then stops process and joins.
		*/
		inline void safe_join(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each cecks to the queues size.*/
		)
		{
			if (!isQueueRunning())
				return;
			WaitForQueueEmpty(ns);
			stopQueue();
			WaitForQueueStop();
		}

		/**
			\brief Posts stop queue message then waits for thread to join.

			<b>Note</b> : Even if queue has messages left over, it will exit 
			and messages will be destroyed.
		*/
		inline void force_join()
		{
			if (!isQueueRunning())
				return;
			stopQueue();
			WaitForQueueStop();
		}

		/**
			\brief The function to wait till instruction queue is empty.
		*/
		inline void WaitForQueueEmpty(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each cecks to the queues size.*/
		) noexcept
		{
			while (true)
			{
				O3_LIB_LOG_LINE;
				std::this_thread::sleep_for(ns);
				bool ret = false;
				{
					std::lock_guard<std::mutex> lock(mtxQueue);
					ret = QueuedMessage.empty();
				}
				if (ret)
					return;
				O3_LIB_LOG_LINE;
			}
			return;
		}

		/**
			\brief The destructor. Exits without waiting for queue stop.
		*/
		~QueuedProcess()
		{
			force_join();
		}
	};

}

#endif
