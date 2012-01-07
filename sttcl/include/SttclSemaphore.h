/*
 * SttclSemaphore.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLSEMAPHORE_H_
#define STTCLSEMAPHORE_H_

#include "SttclTime.h"

#if defined(STTCL_POSIX_SEMAPHORE)
#include "../PosixThreads/SttclPosixSemaphore.h"
#define DEFAULT_SEMAPHOREIMPL sttcl::SttclPosixSemaphore
#elif defined(STTCL_BOOST_SEMAPHORE)
#include "../BoostThreads/SttclBoostSemaphore.h"
#define DEFAULT_SEMAPHOREIMPL sttcl::SttclBoostSemaphore
#endif

#ifndef DEFAULT_SEMAPHOREIMPL
#error "You need to define a default semaphore implementation for sttcl"
#endif

namespace sttcl
{

template<class Impl = DEFAULT_SEMAPHOREIMPL>
class SttclSemaphore
: public Impl
{
public:
	SttclSemaphore(unsigned int initialCount) : Impl(initialCount) {}
	~SttclSemaphore() {}

	void wait()
	{
		static_cast<Impl*>(this)->wait();
	}
	bool try_wait(const TimeDuration<>& timeout = TimeDuration<>::Zero)
	{
		return static_cast<Impl*>(this)->try_wait(timeout);
	}
	void post()
	{
		static_cast<Impl*>(this)->post();
	}
};

}

#endif /* STTCLSEMAPHORE_H_ */
