/**
 * @file SttclMutex.h
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

#ifndef STTCLMUTEX_H_
#define STTCLMUTEX_H_

#include "SttclTime.h"

#ifndef STTCL_DEFAULT_MUTEXIMPL
#if defined(STTCL_POSIX_THREADS) or defined(STTCL_POSIX_IMPL)
#include "../PosixThreads/SttclPosixMutex.h"
#define STTCL_DEFAULT_MUTEXIMPL sttcl::internal::posix_impl::SttclPosixMutex
#elif defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include "../BoostThreads/SttclBoostMutex.h"
#define STTCL_DEFAULT_MUTEXIMPL sttcl::internal::boost_impl::SttclBoostMutex
#elif defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
#include "../C++11Threads/SttclCx11Mutex.h"
#define STTCL_DEFAULT_MUTEXIMPL sttcl::internal::cx11_impl::SttclCx11tMutex
#endif

#ifndef STTCL_DEFAULT_MUTEXIMPL
#error "You need to define a default mutex implementation for sttcl"
#endif
#endif

namespace sttcl
{

namespace internal
{

/**
 * Adapter class for a (OS-)specific mutex implementation.
 * @tparam Impl Selects a (OS-)specific mutex implementation.
 *
 * @todo Implement a static interface check for the Impl class.
 */
template
< class Impl = STTCL_DEFAULT_MUTEXIMPL
, class TimeDurationType = TimeDuration<STTCL_DEFAULT_TIMEDURATIONIMPL>
>
class SttclMutex
: public Impl
{
public:
	/**
	 * Constructor for class SttclMutex.
	 */
	SttclMutex() : Impl() {}
	/**
	 * Destructor for class SttclMutex.
	 */
	~SttclMutex() {}

	/**
	 * Locks the mutex. Waits blocking forever until the mutex becomes lockable.
	 */
	void lock()
	{
		static_cast<Impl*>(this)->lock();
	}

	/**
	 * Tries to lock the mutex within the specified \em timeout parameter.
	 * The \em timeout value TimeDurationType::Zero will return success or failure
	 * immediately.
	 * @param timeout The maximum duration to wait until the mutex becomes lockable.
	 * @return \c true if the mutex is lockable. \c false if the \em timeout duration
	 * expired.
	 */
	bool try_lock(const TimeDurationType& timeout = TimeDurationType::Zero)
	{
		return static_cast<Impl*>(this)->try_lock(timeout);
	}

	/**
	 * Unlocks the mutex.
	 */
	void unlock()
	{
		static_cast<Impl*>(this)->unlock();
	}
};

/**
 * Helper class to create a properly scoped lock of a mutex object.
 * @tparam Lockable The mutex class type.
 */
template<class Lockable>
class AutoLocker
{
public:
	/**
	 * Constructor for class AutoLocker. Locks the \em argLockableRef object.
	 * @param argLockableRef A reference to a mutex (or other \em Lockable implementation).
	 */
	AutoLocker(Lockable& argLockableRef)
	: ref(argLockableRef)
	{
		ref.lock();
	}

	/**
	 * Destructor for class AutoLocker. Unlocks the object reference passed with the constructor.
	 */
	~AutoLocker()
	{
		ref.unlock();
	}
private:
	Lockable& ref;
};

}
}

#endif /* STTCLMUTEX_H_ */
