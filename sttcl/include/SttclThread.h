/**
 * @file SttclThread.h
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

#ifndef STTCLTHREAD_H_
#define STTCLTHREAD_H_

#ifndef STTCL_DEFAULT_THREADIMPL
#if defined(STTCL_POSIX_THREADS) or defined(STTCL_POSIX_IMPL)
#include "../PosixThreads/SttclPosixThread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::posix_impl::SttclPosixThread
#elif defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include "../BoostThreads/SttclBoostThread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::boost_impl::SttclBoostThread
#elif defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
#include "../C++11Threads/SttclCx11Thread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::cx11_impl::SttclCx11Thread
#endif

#ifndef STTCL_DEFAULT_THREADIMPL
#error "You need to define a default thread implementation for sttcl"
#endif
#endif

namespace sttcl
{

namespace internal
{

/**
 * Adapter class for a (OS-)specific thread implementation.
 * @tparam Impl Selects a (OS-)specific thread implementation.
 *
 * @todo Implement a static interface check for the Impl class.
 */
template<class Impl = STTCL_DEFAULT_THREADIMPL>
class SttclThread
: public Impl
{
public:
	/**
	 * Defines the method pointer signature used for the thread method.
	 */
	typedef void* (*ThreadMethodPtr)(void*);

	/**
	 * Constructor for class SttclThread.
	 * @param argThreadMethod A pointer tor the method that should be executed as thread method.
	 */
	SttclThread(ThreadMethodPtr argThreadMethod) : Impl(argThreadMethod)
	{
	}
	/**
	 * Destructor for class SttclThread.
	 */
	~SttclThread() {}

	/**
	 * Runs the thread method within a separate thread.
	 */
	bool run(void* args)
	{
		return static_cast<Impl*>(this)->run(args);
	}

	/**
	 * Waits blocking forever until the thread method exits.
	 */
	void join()
	{
		static_cast<Impl*>(this)->join();
	}

	/**
	 * Kills the thread method.
	 */
	void detach()
	{
		static_cast<Impl*>(this)->detach();
	}

	/**
	 * Returns \c true if the other thread reference represents the thread method path, \c false
	 * otherwise.
	 * @param otherThread A thread reference.
	 */
	static bool isSelf(const Impl& otherThread)
	{
		return Impl::isSelf(otherThread);
	}

private:
	SttclThread(); //!< Forbidden
	SttclThread(const SttclThread<Impl>& rhs); //!< Forbidden
	SttclThread& operator=(const SttclThread<Impl>& rhs); //!< Forbidden
};
}
}

#endif /* STTCLTHREAD_H_ */
