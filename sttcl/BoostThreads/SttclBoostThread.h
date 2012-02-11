/*
 * SttclBoostThread.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTTHREAD_H_
#define STTCLBOOSTTHREAD_H_

#if defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include <boost/thread.hpp>
namespace sttcl
{
namespace internal
{
namespace boost_impl
{
/**
 * The boost default implementation for sttcl::SttclThread<>.
 */
class SttclBoostThread
{
public:
	typedef boost::thread ThreadNativeType;

	typedef void* (*ThreadMethodPtr)(void*);

	SttclBoostThread(ThreadMethodPtr argThreadMethod);
	virtual ~SttclBoostThread();

	bool run(void* args);
	void join();
	void detach();
	static bool isSelf(const SttclBoostThread& otherThread);

private:
	ThreadMethodPtr threadMethod;
	ThreadNativeType thread;

};
}
}
}

#endif
#endif /* STTCLBOOSTTHREAD_H_ */
