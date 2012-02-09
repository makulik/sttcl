/*
 * SttclPosixSemaphore.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclPosixSemaphore.h"
#ifdef STTCL_POSIX_THREADS

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::posix_impl;
using sttcl::internal::posix_impl::SttclPosixSemaphore;

SttclPosixSemaphore::SttclPosixSemaphore(unsigned int initialCount)
{
	sem_init(&semaphore,0,initialCount);
}

SttclPosixSemaphore::~SttclPosixSemaphore()
{
	sem_destroy(&semaphore);
}

void SttclPosixSemaphore::wait()
{
	sem_wait(&semaphore);
}

bool SttclPosixSemaphore::try_wait(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		int ret = sem_trywait(&semaphore);
		if(ret < 0)
		{
			return false;
		}
		return true;
	}


	struct timespec abstime;
	abstime.tv_sec = timeout.seconds();
	abstime.tv_nsec = timeout.nanoseconds();
	int ret = sem_timedwait(&semaphore,&abstime);
	if(ret <= 0)
	{
		return false;
	}
	return true;
}

void SttclPosixSemaphore::post()
{
	sem_post(&semaphore);
}
#endif
