/*
 * SttclMutex.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLMUTEX_H_
#define STTCLMUTEX_H_

#include "SttclTime.h"

#if defined(STTCL_POSIX_THREADS)
#include "../PosixThreads/SttclPosixMutex.h"
#define DEFAULT_MUTEXIMPL sttcl::SttclPosixMutex
#elif defined(STTCL_BOOST_THREADS)
#include "../BoostThreads/SttclBoostMutex.h"
#define DEFAULT_MUTEXIMPL sttcl::SttclBoostMutex
#endif

#ifndef DEFAULT_MUTEXIMPL
#error "You need to define a default mutex implementation for sttcl"
#endif

namespace sttcl
{

template<class Impl = DEFAULT_MUTEXIMPL>
class SttclMutex
: public Impl
{
public:
	SttclMutex() : Impl() {}
	~SttclMutex() {}

	void lock()
	{
		static_cast<Impl*>(this)->lock();
	}
	bool try_lock(const TimeDuration<>& timeout = TimeDuration<>::Zero)
	{
		return static_cast<Impl*>(this)->try_lock(timeout);
	}
	void unlock()
	{
		static_cast<Impl*>(this)->unlock();
	}
};

template<class Lockable>
class AutoLocker
{
public:
	AutoLocker(Lockable& argRef)
	: ref(argRef)
	{
		ref.lock();
	}

	~AutoLocker()
	{
		ref.unlock();
	}
private:
	Lockable& ref;
};
}

#endif /* STTCLMUTEX_H_ */
