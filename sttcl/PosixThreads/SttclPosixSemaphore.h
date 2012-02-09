/*
 * SttclPosixSemaphore.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLPOSIXSEMAPHORE_H_
#define STTCLPOSIXSEMAPHORE_H_

#ifdef STTCL_POSIX_THREADS

#include <semaphore.h>
#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace posix_impl
{
/**
 * The POSIX default implementation for sttcl::SttclSemaphore<>.
 */
class SttclPosixSemaphore
{
public:
	typedef sem_t NativeSemaphoreType;

	SttclPosixSemaphore(unsigned int initialCount);
	virtual ~SttclPosixSemaphore();

	void wait();
	bool try_wait(const TimeDuration<>& timeout);
	void post();

private:
	NativeSemaphoreType semaphore;
};

}
}
}

#endif
#endif /* STTCLPOSIXSEMAPHORE_H_ */
