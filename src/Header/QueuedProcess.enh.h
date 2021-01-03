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

#include "ErrorTracker.enh.h"

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

		Message op code.

		lower and upper arguments.
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

		Message op code.

		lower, upper and another fourth argument.

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
	class BlankType {};

	/**
		\brief The class to implement a structure which executes instructions
		concurently after fetching them through a queue for final use
		including debug calls.


		hasErrorHandlers        = false;\n

		The function registerHandlerFunction must be called to setup the processing function
		before starting the queue process.\n\n

		<h3>Template arguments</h3>
		 
		 -#  <code>class Instruct</code> : The type to tore the instruction.\n

		
		<h3> How To Use </h3>

		- Create a structure that contains information to be sequentially 
		processed. Let it be `struct info`. You can use structures 
		`GenInstruct` and `QuadInstruct` to merge different types easily.
		The type must be copy-constructible. Let it be `info`.

		- Create a Function of type QueuedProcess::MessageHandlerType returns 
		`Tristate`, takes `info` as argument. The function should return 
		something other than Tristate::GOOD if a fatal error occurs. Let it 
		be `proc`.

		- Create object of `QueuedProcess<info>`, construct by passing `proc`
		 or default construct then call `registerHandlerFunction(proc)`.

		- Call `startQueueExecution` to start waiting on messages.

		- Call `postMessage` and pass the message to add message to queue.

		- Call `stopQueueExecution` to stop processing.

		- Call `WaitForQueueExecutionStop` to wait till queued execution thread stops.
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
		using InfoType = Instruct;

		/**
			\brief The function type that processes the infomation passed.
		*/
		using MessageHandlerType = std::function<Tristate(InfoType)>;

	private:

		/**
			\brief The synchronising mutex for Queue.
		*/
		std::mutex _QueueSyncMutex;

		/**
			\brief The Queue to pass instruction from main to instruction processor.
		*/
		std::queue<InfoType> _queuedMessage;

		/**
			\brief The object to notify update to queue.
		*/
		std::condition_variable _QueueUpdateNotifier;

		/**
			\brief The bool value which indicates whether queue has been
			updated to avoid false wake-ups.
		*/
		std::atomic<bool> _isUpdated;

		/**
			\brief The bool variable which signals the instruction processing
			function to stop and exit after emptying the queue.
		*/
		std::atomic<bool> _shouldStopQueue;

		/**
			\brief sets to true if Queued instruction processor is active.
		*/
		std::atomic<bool> _isQueueActive;

		/**
			\brief The function which processes the instruction then.
		*/
		MessageHandlerType _messageHandlerFunction;

		/**
			\brief The thread handle for the queue process.
		*/
		std::thread _queueHandlerThread;



		/**
			\brief loops and executes tasks pushed into message queue until
			EXIT_QUEUE is pushed into the queue.


			<h3>Return</h3>
			Returns Tristate::ERROR if any msg_switch fails.\n
			Returns Tristate::PREV_ERROR if error was flagged in any previous
			function calls.\n

		*/
		Tristate queueExecutionFunction() noexcept
		{
			O1_LIB_LOG_LINE;
			if (!_messageHandlerFunction)
				return Tristate::ERROR;
			O1_LIB_LOG_LINE;
			while (!(_shouldStopQueue.load()))  // If should stop is asserted, quit.
			{
				O3_LIB_LOG_LINE;
				while (!(isQueueUpdated()))   // Continue waiting till queue is updated
				{
					std::unique_lock<std::mutex> lock(_QueueSyncMutex);
					_QueueUpdateNotifier.wait(lock);
					bool empty = _queuedMessage.empty();
					lock.unlock();
					if (!(isQueueUpdated()) && _shouldStopQueue.load() && empty)  
						// if update is asserted but queue is empty and stop 
						// is asserted, quit
						return (Tristate::GOOD);

				}
				_isUpdated = false;
				bool shouldStopNow = false;
				{
					std::lock_guard<std::mutex> lock(_QueueSyncMutex);
					shouldStopNow = _queuedMessage.empty() || _shouldStopQueue.load();
				} // stop if queue us empty or shouldStop is asserted.
				while (!shouldStopNow)
				{
					O3_LIB_LOG_LINE;
					_QueueSyncMutex.lock();
					InfoType front = _queuedMessage.front();
					_queuedMessage.pop();
					_QueueSyncMutex.unlock();
					Tristate ret = _messageHandlerFunction(front);
					if (!ret)
						return (Tristate::ERROR);
					std::lock_guard<std::mutex> temp_lock(_QueueSyncMutex);
					shouldStopNow = _queuedMessage.empty() || _shouldStopQueue.load();
				}

			}
			O4_LIB_LOG_LINE;
			return (Tristate::GOOD);
		}

	public:

		

		/**
			\brief The default constructor.
		*/
		QueuedProcess() noexcept : _queueHandlerThread()
		{
			_isUpdated = false;
			_shouldStopQueue = false;
			_isQueueActive = false;
		}

		/**
			\brief Registers the processing method while constructing.
		*/
		explicit QueuedProcess(
			MessageHandlerType msgHandler /**< : <i>in</i> : The procedure.*/
		) noexcept : _queueHandlerThread()
		{
			_isUpdated = false;
			_shouldStopQueue = false;
			_isQueueActive = false;
			_messageHandlerFunction = msgHandler;
		}

		QueuedProcess(const QueuedProcess&) = delete;

		QueuedProcess(QueuedProcess&&) = delete;

		QueuedProcess& operator = (QueuedProcess&&) = delete;

		QueuedProcess& operator = (const QueuedProcess&) = delete;

		/**
			\brief set a function as the instruction processor.
		*/
		inline void registerHandlerFunction(
			MessageHandlerType in /**< : <i>in</i> : The procedure.*/
		) noexcept
		{
			_messageHandlerFunction = in;
		}

		/**
			\brief starts the function queue_process in another thread.

			<h3>Return</h3>
			Returns Tristate::ERROR if no procedure was set, or queue is
			already running.\n
		*/
		Tristate startQueueExecution() noexcept
		{
			O3_LIB_LOG_LINE;
			if (!_messageHandlerFunction)
				return Tristate::ERROR;
			if (isQueueRunning())
				return Tristate::ERROR;
			O2_LIB_LOG_LINE;
			_shouldStopQueue = false;
			_queueHandlerThread = std::thread(
				&QueuedProcess::queueExecutionFunction, this);
			_isQueueActive = true;
			O2_LIB_LOG_LINE;
			return (Tristate::GOOD);
		}

		/**
			\brief Check if queue is updated.

			<h3>Return</h3>
			Returns _isUpdated.\n
		*/
		inline bool isQueueUpdated() noexcept
		{
			return _isUpdated.load();
		}

		/**
			\brief The function post a message onto the queue.
		*/
		inline void postMessage(
			InfoType Message /**< : <i>in</i> : Message need to be pushed.*/
		)
		{
			{
				std::lock_guard<std::mutex> lock(_QueueSyncMutex);
				_queuedMessage.push(Message);
				_isUpdated = true;
			}
			_QueueUpdateNotifier.notify_all();
			return;
		}


		/**
			\brief The function to signal the queue to stop processing after
			emptying the queue.
		*/
		inline void stopQueueExecution() noexcept
		{
			_shouldStopQueue = true;
			_QueueUpdateNotifier.notify_all();
		}


		/**
			\brief Checks if Queue is running.

		  <h3>Return</h3>
		  true if queue is running.\n

		*/
		inline bool isQueueRunning() noexcept { return _isQueueActive.load(); };

		/**
			\brief Waits till Queued process stops execution. Then empties queue.
		*/
		inline void waitForQueueExecutionStop() noexcept
		{
			if (_queueHandlerThread.joinable() || isQueueRunning() )
			{
				O3_LIB_LOG_LINE;
				_queueHandlerThread.join();
				O4_LIB_LOG_LINE;
				_isQueueActive = false;
				_shouldStopQueue = false;
				std::lock_guard<std::mutex> lock(_QueueSyncMutex);
				_queuedMessage = std::queue<Instruct>();
			}

		}

		/**
			\brief Waits till Queue is Empty then stops process and joins.
		*/
		inline void joinAfterQueueEmpty(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each cecks to the queues size.*/
		)
		{
			if (!isQueueRunning())
				return;
			waitForQueueExecutionStop(ns);
			stopQueueExecution();
			waitForQueueExecutionStop();
		}

		/**
			\brief Posts stop queue message then waits for thread to join.

			<b>Note</b> : Even if queue has messages left over, it will exit 
			and messages will be destroyed.
		*/
		inline void forceImmediateJoin()
		{
			if (!isQueueRunning())
				return;
			stopQueueExecution();
			waitForQueueExecutionStop();
		}

		/**
			\brief The function to wait till instruction queue is empty.
		*/
		inline void waitForQueueExecutionStop(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each cecks to the queues size.*/
		) noexcept
		{
			while (true)
			{
				O3_LIB_LOG_LINE;
				bool ret = false;
				{
					std::lock_guard<std::mutex> lock(_QueueSyncMutex);
					ret = _queuedMessage.empty();
				}
				if (ret)
					return;
				std::this_thread::sleep_for(ns);
				O3_LIB_LOG_LINE;
			}
			return;
		}

		/**
			\brief The destructor. Exits without waiting for queue stop.
		*/
		~QueuedProcess()
		{
			forceImmediateJoin();
		}
	};

}

#endif
