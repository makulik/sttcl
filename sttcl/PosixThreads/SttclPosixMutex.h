/*
 * SttclPosixMutex.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLPOSIXMUTEX_H_
#define STTCLPOSIXMUTEX_H_

#include <pthread.h>
#include "../include/SttclTime.h"

#ifdef STTCL_POSIX_THREADS

namespace sttcl
{
namespace internal
{
namespace posix_impl
{

/**
 * The POSIX default implementation for sttcl::SttclMutex<>.
 */
class SttclPosixMutex
{
public:
	SttclPosixMutex();
	~SttclPosixMutex();

	void lock();
	bool try_lock(const TimeDuration& timeout);
	void unlock();

private:
	pthread_mutex_t mutexHandle;
	bool valid;
};

}
}
}
#endif
#endif /* STTCLPOSIXMUTEX_H_ */
