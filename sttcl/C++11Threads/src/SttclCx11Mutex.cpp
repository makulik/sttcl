/*
 * SttclCx11Mutex.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclCx11Mutex.h"
#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::cx11_impl;
using namespace boost::posix_time;
using sttcl::internal::cx11_impl::SttclCx11Mutex;

SttclCx11Mutex::SttclCx11Mutex()
: mutex()
{
}

SttclCx11Mutex::~SttclCx11Mutex()
{
	mutex.unlock();
}

void SttclCx11Mutex::lock()
{
	mutex.lock();
}

bool SttclCx11Mutex::try_lock(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		return mutex.try_lock();
	}

	return mutex.timed_lock(timeout.getNativeValue());
}

void SttclCx11Mutex::unlock()
{
	mutex.unlock();
}
#endif
