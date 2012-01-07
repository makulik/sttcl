/*
 * SttclBoostThread.h
 *
 *  Created on: 26.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTTHREAD_H_
#define STTCLBOOSTTHREAD_H_

#include <boost/thread.hpp>
namespace sttcl
{
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

#endif /* STTCLBOOSTTHREAD_H_ */
