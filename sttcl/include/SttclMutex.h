/*
 * SttclMutex.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
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
#endif

#ifndef STTCL_DEFAULT_MUTEXIMPL
#error "You need to define a default mutex implementation for sttcl"
#endif
#endif

namespace sttcl
{

/**
 * Adapter class for a (OS-)specific mutex implementation.
 * @tparam Impl Selects a (OS-)specific mutex implementation.
 */
template<class Impl = STTCL_DEFAULT_MUTEXIMPL>
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
	 * The \em timeout value TimeDuration<>::Zero will return success or failure
	 * immediately.
	 * @param timeout The maximum duration to wait until the mutex becomes lockable.
	 * @return \c true if the mutex is lockable. \c false if the \em timeout duration
	 * expired.
	 */
	bool try_lock(const TimeDuration<>& timeout = TimeDuration<>::Zero)
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

#endif /* STTCLMUTEX_H_ */
