/**
 * @file SttclSemaphore.h
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
 * 3) Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products
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

#ifndef STTCLSEMAPHORE_H_
#define STTCLSEMAPHORE_H_

#include "SttclTime.h"

#ifndef STTCL_DEFAULT_SEMAPHOREIMPL
#if defined(STTCL_POSIX_SEMAPHORE) or defined(STTCL_POSIX_IMPL)
#include "../PosixThreads/SttclPosixSemaphore.h"
#define STTCL_DEFAULT_SEMAPHOREIMPL sttcl::internal::posix_impl::SttclPosixSemaphore
#elif defined(STTCL_BOOST_SEMAPHORE) or defined(STTCL_BOOST_IMPL)
#include "../BoostThreads/SttclBoostSemaphore.h"
#define STTCL_DEFAULT_SEMAPHOREIMPL sttcl::internal::boost_impl::SttclBoostSemaphore
#elif defined(STTCL_CX11_SEMAPHORE) or defined(STTCL_CX11_IMPL)
#include "../C++11Threads/SttclCx11Semaphore.h"
#define STTCL_DEFAULT_SEMAPHOREIMPL sttcl::internal::cx11_impl::SttclCx11Semaphore
#endif

#ifndef STTCL_DEFAULT_SEMAPHOREIMPL
#error "You need to define a default semaphore implementation for sttcl"
#endif
#endif

namespace sttcl
{

namespace internal
{
/**
 * Adapter class for a (OS-)specific semaphore implementation.
 * @tparam Impl Selects a (OS-)specific semaphore implementation.
 *
 * @todo Implement a static interface check for the Impl class.
 */
template
< class Impl = STTCL_DEFAULT_SEMAPHOREIMPL
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
>
class SttclSemaphore
: public Impl
{
public:
	/**
	 * Constructor for class SttclSemaphore.
	 * @param initialCount Sets the initial semaphore count.
	 */
	SttclSemaphore(unsigned int initialCount = 0) : Impl(initialCount) {}
	/**
	 * Destructor for class SttclSemaphore.
	 */
	~SttclSemaphore() {}

	/**
	 * Waits blocking forever until the semaphore is incremented.
	 */
	void wait()
	{
		static_cast<Impl*>(this)->wait();
	}

	/**
	 * Waits until the semaphore is incremented within the specified \em timeout duration.
	 * A \em timeout value of TimeDurationType::Zero returns the semaphore state immediatly.
	 * @param timeout Specifies the maximum duration to wait until the semaphore is incremented.
	 * @return \c true if the semaphore was successfully decremented.
	 */
	bool try_wait(const TimeDurationType& timeout = TimeDurationType::Zero)
	{
		return static_cast<Impl*>(this)->try_wait(timeout);
	}

	/**
	 * Increments the semaphore.
	 */
	void post()
	{
		static_cast<Impl*>(this)->post();
	}
};

}
}

#endif /* STTCLSEMAPHORE_H_ */
