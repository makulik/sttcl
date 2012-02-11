/*
 * SttclBoostMutex.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTMUTEX_H_
#define STTCLBOOSTMUTEX_H_

#if defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include <boost/thread.hpp>
#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace boost_impl
{
/**
 * The boost default implementation for sttcl::SttclMutex<>.
 */
class SttclBoostMutex
{
public:
	typedef boost::timed_mutex NativeMutexType;
	SttclBoostMutex();
	virtual ~SttclBoostMutex();

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
#endif /* STTCLBOOSTMUTEX_H_ */
