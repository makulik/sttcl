/*
 * SttclPosixThread.cpp
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#include "../SttclPosixThread.h"

#ifdef STTCL_POSIX_THREADS

using namespace sttcl;
using sttcl::SttclPosixThread;

SttclPosixThread::SttclPosixThread(ThreadMethodPtr argThreadMethod)
: threadMethod(argThreadMethod)
, pthreadHandle()
, valid(false)
{
}

SttclPosixThread::~SttclPosixThread()
{
	detach();
}

bool SttclPosixThread::run(void* args)
{
	if(threadMethod && !valid)
	{
		if(pthread_create(&pthreadHandle,NULL,threadMethod,args) == 0)
		{
			valid = true;
		}
	}

	return valid;
}

void SttclPosixThread::join()
{
	if(valid)
	{
		pthread_join(pthreadHandle, NULL);
		valid = false;
	}
}

void SttclPosixThread::detach()
{
	if(valid)
	{
		pthread_detach(pthreadHandle);
		valid = false;
	}
}
#endif
