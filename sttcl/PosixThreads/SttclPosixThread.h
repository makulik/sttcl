/*
 * SttclPosixThread.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLPOSIXTHREAD_H_
#define STTCLPOSIXTHREAD_H_

#ifdef STTCL_POSIX_THREADS

#include <pthread.h>

namespace sttcl
{
namespace internal
{
namespace posix_impl
{
/**
 * The POSIX default implementation for sttcl::SttclThread<>.
 */
class SttclPosixThread
{
public:
	typedef void* (*ThreadMethodPtr)(void*);

	SttclPosixThread(ThreadMethodPtr argThreadMethod);
	virtual ~SttclPosixThread();

	bool run(void* args);
	void join();
	void detach();
private:
	ThreadMethodPtr threadMethod;
	pthread_t pthreadHandle;
	bool valid;
};

}
}
}
#endif
#endif /* STTCLPOSIXTHREAD_H_ */
