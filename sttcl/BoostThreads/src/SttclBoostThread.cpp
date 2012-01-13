/*
 * SttclBoostThread.cpp
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#include "../SttclBoostThread.h"

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::boost_impl;
using sttcl::internal::boost_impl::SttclBoostThread;


SttclBoostThread::SttclBoostThread(ThreadMethodPtr argThreadMethod)
: threadMethod(argThreadMethod)
, thread()
{
	detach();
}

SttclBoostThread::~SttclBoostThread()
{
	if(thread.joinable())
	{
		thread.join();
	}
}

bool SttclBoostThread::run(void* args)
{
	thread = boost::thread(*threadMethod,args);
	return true;
}

void SttclBoostThread::join()
{
	if(thread.joinable())
	{
		thread.join();
	}
}

void SttclBoostThread::detach()
{
	if(thread.joinable())
	{
		thread.detach();
	}
}

bool SttclBoostThread::isSelf(const SttclBoostThread& otherThread)
{
	return boost::this_thread::get_id() == otherThread.thread.get_id();
}
