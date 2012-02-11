/*
 * SttclCx11Semaphore.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclCx11Semaphore.h"

#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::cx11_impl;
using namespace boost::posix_time;
using sttcl::internal::cx11_impl::SttclCx11Semaphore;

SttclCx11Semaphore::SttclCx11Semaphore(unsigned int initialCount)
: semaphore(initialCount)
{
}

SttclCx11Semaphore::~SttclCx11Semaphore()
{
}

void SttclCx11Semaphore::wait()
{
	semaphore.wait();
}

bool SttclCx11Semaphore::try_wait(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		return semaphore.try_wait();
	}

	boost::posix_time::ptime absTime = boost::posix_time::microsec_clock::universal_time() + timeout.getNativeValue();
	return semaphore.timed_wait(absTime);
}

void SttclCx11Semaphore::post()
{
	semaphore.post();
}
#endif
