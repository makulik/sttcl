/*
 * SttclCx11Thread.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLCX11THREAD_H_
#define STTCLCX11THREAD_H_

#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
#include <thread>

namespace sttcl
{
namespace internal
{
namespace cx11_impl
{
/**
 * The C++ 11 standard default implementation for sttcl::SttclThread<>.
 */
class SttclCx11Thread
{
public:
	typedef boost::thread ThreadNativeType;

	typedef void* (*ThreadMethodPtr)(void*);

	SttclCx11Thread(ThreadMethodPtr argThreadMethod);
	virtual ~SttclCx11Thread();

	bool run(void* args);
	void join();
	void detach();
	static bool isSelf(const SttclCx11Thread& otherThread);

private:
	ThreadMethodPtr threadMethod;
	ThreadNativeType thread;

};
}
}
}
#endif
#endif /* STTCLCX11THREAD_H_ */
