/*
 * SttclBoostMutex.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTMUTEX_H_
#define STTCLBOOSTMUTEX_H_

#include <boost/thread.hpp>
#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace boost_impl
{
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

#endif /* STTCLBOOSTMUTEX_H_ */
