/**
 * @file EventQueue.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include "SttclTime.h"
#include "SttclSemaphore.h"
#include "SttclMutex.h"
#if !defined(STTCL_USE_STL)
#else
#include <deque>
#endif

#if !defined(STTCL_USE_STL)
#else
#if !defined(STTCL_DEFAULT_DEQUEIMPL)
#define STTCL_DEFAULT_DEQUEIMPL(__T__) std::deque<__T__>
#endif
#endif

#if !defined(STTCL_DEFAULT_DEQUEIMPL)
#error "You need to define a default double ended queue implementation for sttcl"
#endif

namespace sttcl
{
/**
 * Represents a queue used to dispatch events to a waiting thread.
 */
template
< class T
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
, class SemaphoreType = sttcl::internal::SttclSemaphore<STTCL_DEFAULT_SEMAPHOREIMPL,TimeDurationType>
, class MutexType = sttcl::internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL,TimeDurationType>
, class InnerQueueType = STTCL_DEFAULT_DEQUEIMPL(T)
>
class EventQueue
{
public:
	/**
	 * Constructor for class EventQueue.
	 */
	EventQueue()
	: eventQueue()
	{
	}
	/**
	 * Destructor for class EventQueue.
	 */
	~EventQueue()
	{
	}

	/**
	 * Puts an event to the end of the queue and signals that events are available.
	 * @param event
	 */
	void push_back(const T& event)
	{
		{ sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
			eventQueue.push_back(event);
		}
		eventsAvailable.post();
	}

	/**
	 * Gets the event from the front of the queue.
	 * @return
	 */
	T& front()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		return eventQueue.front();
	}

	/**
	 * Removes the item at front of the queue.
	 */
	void pop_front()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		eventQueue.pop_front();
	}

	/**
	 * Blocks the calling thread until events are available in the queue.
	 * @return \c true if events are available, \c false if an error occurred.
	 */
	bool waitForEvents()
	{
		eventsAvailable.wait();
		return !empty();
	}

	/**
	 * Blocks the calling thread until events are available in the queue.
	 * @return \c true if events are available, \c false if no events were available within the
	 *         specified timeout.
	 */
	bool waitForEvents(TimeDurationType timeout)
	{
		return eventsAvailable.try_wait(timeout) && !empty();
	}

	/**
	 * Indicates that the event queue is empty.
	 * @return \c true if the queue is empty, \c false otherwise.
	 */
	bool empty()
	{
		sttcl::internal::AutoLocker<MutexType> lock(eventQueueMutex);
		return eventQueue.empty();
	}

	/**
	 * Unblocks waiting threads.
	 */
	void unblock()
	{
		eventsAvailable.post();
	}
private:
	EventQueue(const EventQueue<T,TimeDurationType,SemaphoreType,MutexType,InnerQueueType>& rhs); //!< Forbidden
	EventQueue<T,TimeDurationType,SemaphoreType,MutexType,InnerQueueType>& operator=(const EventQueue<T,TimeDurationType,SemaphoreType,MutexType,InnerQueueType>& rhs); //!< Forbidden

	InnerQueueType eventQueue;
	MutexType eventQueueMutex;
	SemaphoreType eventsAvailable;
};


}



#endif /* EVENTQUEUE_H_ */
