/** ***************************************************************************
	\file QueuedHandler.enh.h

	\brief The file to declare class QueuedHandler for concurrent message
		handling

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

#ifndef QUEUED_HANDLER_ENH_H

#	define QUEUED_HANDLER_ENH_H						QueuedHandler.enh.h

#	include "Tristate.enh.h"

#	include <mutex>
#	include <queue>
#	include <condition_variable>
#	include <functional>
#	include <chrono>
#	include <new>
#	include <type_traits>

namespace enh
{

	/**
		\brief The structure to encapsulate an message passed to the
		queue as 3 components.

		Fields: 

		Message op code.

		lower and upper arguments.
		
		<h3>Template arguments</h3>
		 -# <code>class Msg</code> : The type to store message type / op.\n
		 -# <code>class Lower</code> : The type to store first operand.\n
		 -# <code>class Upper</code> : The type to store second operand.\n

		
	*/
	template< class Msg, class Lower, class Upper>
	struct GenericMessage
	{
	public:
		/**
			\brief The field to store message type / op.
		*/
		Msg op;

		/**
			\brief The field to store a first operand / lower Parameter.
		*/
		Lower lParam;

		/**
			\brief The field to store a second operand / upper Parameter.
		*/
		Upper uParam;
	};

	/**
		\brief The structure to encapsulate an message passed to the
		queue as 4 components.

		Fields: 

		Message op code.

		lower, upper and another fourth argument.


		<h3>Template arguments</h3>
		 -# <code>class Msg</code> : The type to store message type / op.\n
		 -# <code>class Lower</code> : The type to store first operand.\n
		 -# <code>class Upper</code> : The type to store second operand.\n
		 -# <code>class Fourth</code> : The type to store last operand.\n

	*/
	template< class Msg, class Lower, class Upper, class Fourth>
	struct QuadMessage
	{
	public:
		/**
			\brief The field to store message type / op..
		*/
		Msg op;

		/**
			\brief The field to store a first operand / lower Parameter.
		*/
		Lower lParam;

		/**
			\brief The field to store a second operand / upper Parameter.
		*/
		Upper uParam;

		/**
			\brief The field to store a third operand / last Parameter.
		*/
		Fourth last;
	};


	/**
		\brief The type to add as place-holder in passing template arguments
		to templates which may not require all types to be valid.
	*/
	class BlankType {};

	/**
		\brief The class to implement a structure which handles messages 
		sequentialy in another thread through a queue.


		The function registerHandlerFunction must be called to setup the 
		handler function before starting the queue process.\n\n

		Construction fails if the type is not copy assignable or copy 
		constructible according to type traits.

		<h3>Template arguments</h3>
		 
		 -#  <code>class Message</code> : The type to store the instruction.\n

		
		<h3> How To Use </h3>

		- Create a structure that contains information to be sequentially 
		processed. Let it be `struct info`. You can use any type. 
		`GenericMessage` and `QuadMessage` to merge different types easily.
		The type must be copy-constructible. Let it be `info`.

		- Create a Function of type QueuedHandler::MessageHandlerType returns 
		`Tristate`, takes `info` as argument. The function should return 
		something other than Tristate::GOOD if a fatal error occurs. Let it 
		be `proc`.

		- Create object of `QueuedHandler<info>`, construct by passing `proc`
		 or default construct then call `registerHandlerFunction(proc)`.

		- Call `startQueueExecution` to start waiting on messages.

		- Call `postMessage` and pass the message to add message to queue.

		- Call `stopQueueExecution` to stop processing.

		- Call `WaitForQueueExecutionStop` to wait till queued execution 
		thread stops. Will only stop after executing full queue unless 
		function returns error.


		<h3>Example</h3>
		
		\include{lineno} queued_process_ex.cpp

	*/
	template<class Message>
	class QueuedHandler 
	{

	public:

		/**
			\brief The type of object to be handled (Message Type)
		*/
		using MessageType = Message;

		static_assert(std::is_copy_assignable_v(MessageType), 
			"Message type must be copy assignable");
		static_assert(std::is_copy_constructible_v(MessageType), 
			"Message type must be copy constructible");

		/**
			\brief The function type that processes the message passed.
		*/
		using MessageHandlerType = std::function<Tristate(MessageType)>;

	private:

		/**
			\brief The synchronising mutex for Queue.
		*/
		std::mutex _QueueSyncMutex;

		/**
			\brief The Queue to pass instruction from main to message handler.
		*/
		std::queue<MessageType> _queuedMessage;

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
			\brief The bool variable which signals the dispatcher
			function to stop and exit after emptying the queue.
		*/
		std::atomic<bool> _shouldStopQueue;

		/**
			\brief sets to true if message dispatcher is active.
		*/
		std::atomic<bool> _isQueueActive;

		/**
			\brief The function which handles the message.
		*/
		MessageHandlerType _messageHandlerFunction;

		/**
			\brief The thread handle for the message dispatcher.
		*/
		std::thread _queueHandlerThread;



		/**
			\brief dispatches message to handler function, quits if handler 
			returns errenously or stop is signaled.

			(dispatcher)

			<h3>Return</h3>
			Returns Tristate::ERROR if any msg_switch fails.\n
			Returns Tristate::PREV_ERROR if error was flagged in any previous
			function calls.\n

		*/
		Tristate queueDispatcher() noexcept
		{
			if (!_messageHandlerFunction)
				return Tristate::ERROR;
			while (!(_shouldStopQueue.load()))  // If should stop is asserted,
												// quit.
			{
				while (!(isQueueUpdated()))   // Continue waiting till queue 
											  // is updated
				{
					std::unique_lock<std::mutex> lock(_QueueSyncMutex);
					_QueueUpdateNotifier.wait(lock);
					bool empty = _queuedMessage.empty();
					lock.unlock();
					if (!(isQueueUpdated()) && _shouldStopQueue.load() 
						&& empty)  
						// if update is asserted but queue is empty and stop 
						// is asserted, quit
						return (Tristate::GOOD);

				}
				_isUpdated = false;
				bool shouldStopNow = false;
				{
					std::lock_guard<std::mutex> lock(_QueueSyncMutex);
					shouldStopNow = _queuedMessage.empty() 
						|| _shouldStopQueue.load();
				} // stop if queue us empty or shouldStop is asserted.
				while (!shouldStopNow)
				{
					_QueueSyncMutex.lock();
					MessageType front = _queuedMessage.front();
					_queuedMessage.pop();
					_QueueSyncMutex.unlock();
					Tristate ret = _messageHandlerFunction(front);
					if (!ret)
					{
						_isQueueActive = false;
						return (Tristate::ERROR); // Handler Fail
					}
					std::lock_guard<std::mutex> temp_lock(_QueueSyncMutex);
					shouldStopNow = _queuedMessage.empty() 
						|| _shouldStopQueue.load();
							// stop if queue us empty or shouldStop is asserted.
				}

			}
			return (Tristate::GOOD);
		}

	public:

		

		/**
			\brief The default constructor.
			
			Queue execution cannot be started until handler function is 
			registered.
		*/
		QueuedHandler() noexcept : _queueHandlerThread()
		{
			_isUpdated = false;
			_shouldStopQueue = false;
			_isQueueActive = false;
		}

		/**
			\brief Registers the processing method while constructing.
		*/
		explicit QueuedHandler(
			MessageHandlerType msgHandler /**< : <i>in</i> : The procedure. */
		) noexcept : _queueHandlerThread()
		{
			_isUpdated = false;
			_shouldStopQueue = false;
			_isQueueActive = false;
			_messageHandlerFunction = msgHandler;
		}

		QueuedHandler(const QueuedHandler&) = delete;

		QueuedHandler(QueuedHandler&&) = delete;

		QueuedHandler& operator = (QueuedHandler&&) = delete;

		QueuedHandler& operator = (const QueuedHandler&) = delete;

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
			\brief starts the function queueDispatcher in another thread.

			<h3>Return</h3>
			Returns Tristate::ERROR if no procedure was set, or queue is
			already running.\n
		*/
		[[nodiscard]] Tristate startDispatcherExecution() noexcept
		{
			if (!_messageHandlerFunction)
				return Tristate::ERROR;
			if (isDispatcherRunning())
				return Tristate::ERROR;
			_shouldStopQueue = false;
			_queueHandlerThread = std::thread(
				&QueuedHandler::queueDispatcher, this);
			_isQueueActive = true;
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
			MessageType Message /**< : <i>in</i> : Message need to be pushed.*/
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
			\brief The function to signal the queue to stop dispatcher.
		*/
		inline void signalDispatcherStop() noexcept
		{
			_shouldStopQueue = true;
			_QueueUpdateNotifier.notify_all();
		}


		/**
			\brief Checks if dispatcher is running.

		  <h3>Return</h3>
		  true if dispatcher is running.\n

		*/
		inline bool isDispatcherRunning() noexcept 
		{ 
			return _isQueueActive.load(); 
		};

		/**
			\brief Waits till dispatcher exits, then empties queue.
		*/
		inline void waitForDispatcherExit() noexcept
		{
			if (_queueHandlerThread.joinable() || isDispatcherRunning() )
			{
				_queueHandlerThread.join();
				_isQueueActive = false;
				_shouldStopQueue = false;
				std::lock_guard<std::mutex> lock(_QueueSyncMutex);
				_queuedMessage = std::queue<MessageType>();
			}

		}

		/**
			\brief Waits till Queue is Empty then signals dispatcher exit
			then waits for it to exit.
		*/
		inline void joinAfterQueueEmpty(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each checks to the queues size.*/
		) noexcept
		{
			if (!isDispatcherRunning())
				return;
			waitForQueueEmpty(ns);
			signalDispatcherStop();
			waitForDispatcherExit();
		}

		/**
			\brief Issues immediate exit signal and waits for exit.

			<b>Note</b> : Even if queue has messages left over, it will exit 
			and messages will be destroyed.
		*/
		inline void forceImmediateJoin() noexcept
		{
			if (!isDispatcherRunning())
				return;
			signalDispatcherStop();
			waitForDispatcherExit();
		}

		/**
			\brief The function to wait till message queue is empty.
		*/
		inline void waitForQueueEmpty(
			std::chrono::nanoseconds ns /**< : <i>in</i> : The amount of time
							to wait between each cecks to the queues size.*/
		) noexcept
		{
			while (true)
			{
				bool ret = false;
				{
					std::lock_guard<std::mutex> lock(_QueueSyncMutex);
					ret = _queuedMessage.empty();
				}
				if (ret)
					return;
				std::this_thread::sleep_for(ns);
			}
			return;
		}

		/**
			\brief The destructor. forces immediate exit.
		*/
		~QueuedHandler()
		{
			forceImmediateJoin();
		}
	};

}

#endif
