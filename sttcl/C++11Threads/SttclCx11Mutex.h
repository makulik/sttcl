/*
 * SttclCx11Mutex.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLCX11MUTEX_H_
#define STTCLCX11MUTEX_H_
#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)

#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace cx11_impl
{
/**
 * The C++ 11 standard default implementation for sttcl::SttclMutex<>.
 */
class SttclCx11Mutex
{
public:
	typedef boost::timed_mutex NativeMutexType;
	SttclCx11Mutex();
	virtual ~SttclCx11Mutex();

	void lock();
	bool try_lock(const TimeDuration<>& timeout);
	void unlock();

private:
	NativeMutexType mutex;
};

}
}
}
#endif
#endif /* STTCLCX11MUTEX_H_ */
