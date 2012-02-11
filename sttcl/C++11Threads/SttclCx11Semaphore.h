/*
 * SttclCx11Semaphore.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLCX11SEMAPHORE_H_
#define STTCLCX11SEMAPHORE_H_

#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)

#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace cx11_impl
{
/**
 * The C++ 11 standard default implementation for sttcl::SttclSemaphore<>.
 */
class SttclCx11Semaphore
{
public:
	typedef boost::interprocess::interprocess_semaphore NativeSemaphoreType;
	SttclCx11Semaphore(unsigned int initialCount);
	virtual ~SttclSemaphore();

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
#endif /* STTCLCX11SEMAPHORE_H_ */
