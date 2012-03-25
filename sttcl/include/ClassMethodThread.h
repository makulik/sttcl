/**
 * @file ClassMethodThread.h
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

#ifndef CLASSMETHODTHREAD_H_
#define CLASSMETHODTHREAD_H_

#include "SttclThread.h"
#include "SttclMutex.h"

namespace sttcl
{
/**
 * Represents a thread running a class member method of \em T.
 * @tparam T The class providing the thread method.
 * @tparam UserArgs The optional user arguments type passed to the thread method, the default is
 *                  void.
 * @tparam The optional thread class implementation, the default is STTCL_DEFAULT_THREADIMPL.
 */
template
< class T
, class UserArgs = void
, class ThreadImpl = STTCL_DEFAULT_THREADIMPL
, class MutexImpl = STTCL_DEFAULT_MUTEXIMPL
>
class ClassMethodThread
: public sttcl::internal::SttclThread<ThreadImpl>
{
public:
	/**
	 * Defines the method pointer signature used for the thread method.
	 */
	typedef void* (T::*ThreadMethodPtr)(UserArgs*);

private:
	struct RunArgs
	{
		ClassMethodThread<T,UserArgs,ThreadImpl,MutexImpl>* threadInstance;
		T* instance;
		ThreadMethodPtr threadMethod;
		UserArgs* userArgs;

		RunArgs(ClassMethodThread<T,UserArgs,ThreadImpl,MutexImpl>* argThreadInstance,T* argInstance, ThreadMethodPtr argThreadMethod, UserArgs* argUserArgs = 0)
		: threadInstance(argThreadInstance)
		, instance(argInstance)
		, threadMethod(argThreadMethod)
		, userArgs(argUserArgs)
		{
		}
		RunArgs(const RunArgs& rhs)
		: threadInstance(rhs.threadInstance)
		, instance(rhs.instance)
		, threadMethod(rhs.threadMethod)
		, userArgs(rhs.userArgs)
		{
		}
		RunArgs& operator=(const RunArgs& rhs)
		{
			threadInstance = rhs.threadInstance;
			instance = rhs.instance;
			threadMethod = rhs.threadMethod;
			userArgs = rhs.userArgs;
			return *this;
		}

	private:
		RunArgs(); //!< Forbidden
	};
public:
	/**
	 * Constructor for the ClassMethodThread class.
	 * @param argInstance The instance providing the thread method.
	 * @param argThreadMethod A function pointer for the thread method.
	 */
	ClassMethodThread(T* argInstance, ThreadMethodPtr argThreadMethod)
	: sttcl::internal::SttclThread<ThreadImpl>(internalThreadMethod)
	, runArgs(this,argInstance,argThreadMethod)
	, running(false)
	, threadMutex()
	{
	}

	/**
	 * Destructor for the ClassMethodThread class.
	 */
	virtual ~ClassMethodThread()
	{
	}

	/**
	 * Runs the thread method within a separate thread.
	 * @param userArgs Arguments passed to the thread method.
	 */
	bool run(UserArgs* userArgs = 0)
	{
		if(!isRunning())
		{
			runArgs.userArgs = userArgs;
			return sttcl::internal::SttclThread<ThreadImpl>::run(&runArgs);
		}
		return false;
	}

	bool isRunning()
	{
		sttcl::internal::AutoLocker<MutexImpl> lock(threadMutex);
		return running;
	}

	void join()
	{
		if(!isSelf(*this))
		{
			sttcl::internal::SttclThread<ThreadImpl>::join();
		}
	}

private:
	static void* internalThreadMethod(void* args)
	{
		void * result = 0;
		RunArgs* runArgs = reinterpret_cast<RunArgs*>(args);
		ClassMethodThread<T,UserArgs,ThreadImpl,MutexImpl>* thisPtr = runArgs->threadInstance;

//		if(!isSelf(*thisPtr) && !thisPtr->isRunning())
//		{
			{ sttcl::internal::AutoLocker<MutexImpl> lock(thisPtr->threadMutex);
				thisPtr->running = true;
			}
			T* instance = runArgs->instance;
			ThreadMethodPtr threadMethod = runArgs->threadMethod;
			result = (instance->*threadMethod)(runArgs->userArgs);
			{ sttcl::internal::AutoLocker<MutexImpl> lock(thisPtr->threadMutex);
				thisPtr->running = false;
			}
//		}
		return result;
	}

	ClassMethodThread(); //!< Forbidden
	ClassMethodThread(const ClassMethodThread<T,UserArgs,ThreadImpl>& rhs); //!< Forbidden
	ClassMethodThread<T,UserArgs,ThreadImpl>& operator=(const ClassMethodThread<T,UserArgs,ThreadImpl>& rhs); //!< Forbidden

	RunArgs runArgs;
	bool running;
	MutexImpl threadMutex;
};

}
#endif /* CLASSMETHODTHREAD_H_ */
