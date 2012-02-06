/*
 * SttclBoostSemaphore.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclBoostSemaphore.h"
#include <boost/date_time/posix_time/ptime.hpp>

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::boost_impl;
using namespace boost::posix_time;
using sttcl::internal::boost_impl::SttclBoostSemaphore;

SttclBoostSemaphore::SttclBoostSemaphore(unsigned int initialCount)
: semaphore(initialCount)
{
}

SttclBoostSemaphore::~SttclBoostSemaphore()
{
}

void SttclBoostSemaphore::wait()
{
	semaphore.wait();
}

bool SttclBoostSemaphore::try_wait(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		return semaphore.try_wait();
	}

	boost::posix_time::ptime absTime = boost::posix_time::microsec_clock::universal_time() + timeout.getNativeValue();
	return semaphore.timed_wait(absTime);
}

void SttclBoostSemaphore::post()
{
	semaphore.post();
}
