/*
 * SttclThread.h
 *
 *  Created on: 19.12.2011
 *      Author: Admin
 */

#ifndef STTCLTHREAD_H_
#define STTCLTHREAD_H_

#ifndef STTCL_DEFAULT_THREADIMPL
#if defined(STTCL_POSIX_THREADS) or defined(STTCL_POSIX_IMPL)
#include "../PosixThreads/SttclPosixThread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::posix_impl::SttclPosixThread
#elif defined(STTCL_BOOST_THREADS) or defined(STTCL_BOOST_IMPL)
#include "../BoostThreads/SttclBoostThread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::boost_impl::SttclBoostThread
#elif defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
#include "../C++11Threads/SttclCx11Thread.h"
#define STTCL_DEFAULT_THREADIMPL sttcl::internal::cx11_impl::SttclCx11Thread
#endif

#ifndef STTCL_DEFAULT_THREADIMPL
#error "You need to define a default thread implementation for sttcl"
#endif
#endif

namespace sttcl
{

namespace internal
{

/**
 * Adapter class for a (OS-)specific thread implementation.
 * @tparam Impl Selects a (OS-)specific thread implementation.
 *
 * @todo Implement a static interface check for the Impl class.
 */
template<class Impl = STTCL_DEFAULT_THREADIMPL>
class SttclThread
: public Impl
{
public:
	/**
	 * Defines the method pointer signature used for the thread method.
	 */
	typedef void* (*ThreadMethodPtr)(void*);

	/**
	 * Constructor for class SttclThread.
	 * @param argThreadMethod A pointer tor the method that should be executed as thread method.
	 */
	SttclThread(ThreadMethodPtr argThreadMethod) : Impl(argThreadMethod)
	{
	}
	/**
	 * Destructor for class SttclThread.
	 */
	~SttclThread() {}

	/**
	 * Runs the thread method within a separate thread.
	 */
	bool run(void* args)
	{
		return static_cast<Impl*>(this)->run(args);
	}

	/**
	 * Waits blocking forever until the thread method exits.
	 */
	void join()
	{
		static_cast<Impl*>(this)->join();
	}

	/**
	 * Kills the thread method.
	 */
	void detach()
	{
		static_cast<Impl*>(this)->detach();
	}

	/**
	 * Returns \c true if the other thread reference represents the thread method path, \c false
	 * otherwise.
	 * @param otherThread A thread reference.
	 */
	static bool isSelf(const Impl& otherThread)
	{
		return Impl::isSelf(otherThread);
	}

private:
	SttclThread(); //!< Forbidden
	SttclThread(const SttclThread<Impl>& rhs); //!< Forbidden
	SttclThread& operator=(const SttclThread<Impl>& rhs); //!< Forbidden
};
}
}

#endif /* STTCLTHREAD_H_ */
