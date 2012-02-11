/*
 * SttclBoostSemaphore.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTSEMAPHORE_H_
#define STTCLBOOSTSEMAPHORE_H_

#if defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace boost_impl
{
/**
 * The boost default implementation for sttcl::SttclSemaphore<>.
 */
class SttclBoostSemaphore
{
public:
	typedef boost::interprocess::interprocess_semaphore NativeSemaphoreType;
	SttclBoostSemaphore(unsigned int initialCount);
	virtual ~SttclBoostSemaphore();

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
#endif /* STTCLBOOSTSEMAPHORE_H_ */
