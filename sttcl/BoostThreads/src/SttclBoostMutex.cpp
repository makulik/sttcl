/*
 * SttclBoostMutex.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclBoostMutex.h"
#include <boost/date_time/posix_time/ptime.hpp>

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::boost_impl;
using namespace boost::posix_time;
using sttcl::internal::boost_impl::SttclBoostMutex;

SttclBoostMutex::SttclBoostMutex()
: mutex()
{
}

SttclBoostMutex::~SttclBoostMutex()
{
	mutex.unlock();
}

void SttclBoostMutex::lock()
{
	mutex.lock();
}

bool SttclBoostMutex::try_lock(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		return mutex.try_lock();
	}

	return mutex.timed_lock(timeout.getNativeValue());
}

void SttclBoostMutex::unlock()
{
	mutex.unlock();
}
