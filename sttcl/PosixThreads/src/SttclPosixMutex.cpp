/*
 * SttclPosixMutex.cpp
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#include "../SttclPosixMutex.h"
#ifdef STTCL_POSIX_THREADS

#include <time.h>

using namespace sttcl;
using sttcl::SttclPosixMutex;

SttclPosixMutex::SttclPosixMutex()
: mutexHandle()
, valid(false)
{
	if(pthread_mutex_init(&mutexHandle,NULL) == 0)
	{
		valid = true;
	}
}

SttclPosixMutex::~SttclPosixMutex()
{
	if(valid)
	{
		pthread_mutex_destroy(&mutexHandle);
		valid = false;
	}
}

void SttclPosixMutex::lock()
{
	if(valid)
	{
		pthread_mutex_lock(&mutexHandle);
	}
}

bool SttclPosixMutex::try_lock(const TimeDuration& timeout)
{
	if(valid)
	{
		if(timeout == TimeDuration::Zero)
		{
			if(pthread_mutex_trylock(&mutexHandle) == 0)
			{
				return true;
			}
		}
		else
		{
			struct timespec now;
			clock_gettime(CLOCK_REALTIME,&now);
			TimeDuration tv(now.tv_sec,now.tv_nsec);
			tv += timeout;
			struct timespec until;
			until.tv_sec = tv.getSeconds();
			until.tv_nsec = tv.getNanoSeconds();
			if(pthread_mutex_timedlock(&mutexHandle,&until) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

void SttclPosixMutex::unlock()
{
	if(valid)
	{
		pthread_mutex_unlock(&mutexHandle);
	}
}
#endif
