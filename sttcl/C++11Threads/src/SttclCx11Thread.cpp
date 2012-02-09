/*
 * SttclCx11Thread.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclCx11Thread.h"
#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::cx11_impl;
using sttcl::internal::cx11_impl::SttclCx11Thread;


SttclCx11Thread::SttclCx11Thread(ThreadMethodPtr argThreadMethod)
: threadMethod(argThreadMethod)
, thread()
{
	detach();
}

SttclCx11Thread::~SttclCx11Thread()
{
	if(thread.joinable())
	{
		thread.join();
	}
}

bool SttclCx11Thread::run(void* args)
{
	thread = boost::thread(*threadMethod,args);
	return true;
}

void SttclCx11Thread::join()
{
	if(thread.joinable())
	{
		thread.join();
	}
}

void SttclCx11Thread::detach()
{
	if(thread.joinable())
	{
		thread.detach();
	}
}

bool SttclCx11Thread::isSelf(const SttclCx11Thread& otherThread)
{
	return boost::this_thread::get_id() == otherThread.thread.get_id();
}
#endif
