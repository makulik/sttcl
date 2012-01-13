/*
 * SttclThread.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLTHREAD_H_
#define STTCLTHREAD_H_

#if defined(STTCL_POSIX_THREADS)
#include "../PosixThreads/SttclPosixThread.h"
#define DEFAULT_THREADIMPL sttcl::internal::posix_impl::SttclPosixThread
#elif defined(STTCL_BOOST_THREADS)
#include "../BoostThreads/SttclBoostThread.h"
#define DEFAULT_THREADIMPL sttcl::internal::boost_impl::SttclBoostThread
#endif

#ifndef DEFAULT_THREADIMPL
#error "You need to define a default thread implementation for sttcl"
#endif

namespace sttcl
{

template<class Impl = DEFAULT_THREADIMPL>
class SttclThread
: public Impl
{
public:
	typedef void* (*ThreadMethodPtr)(void*);

	SttclThread(ThreadMethodPtr argThreadMethod) : Impl(argThreadMethod) {}
	~SttclThread() {}

	bool run(void* args)
	{
		return static_cast<Impl*>(this)->run(args);
	}
	void join()
	{
		static_cast<Impl*>(this)->join();
	}
	void detach()
	{
		static_cast<Impl*>(this)->detach();
	}
	static bool isSelf(const Impl& otherThread)
	{
		return Impl::isSelf(otherThread);
	}
};

}

#endif /* STTCLTHREAD_H_ */
