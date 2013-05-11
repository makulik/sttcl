/*
 * ITestConcurrentStateMachineWithArgs.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ITESTCONCURRENTSTATEMACHINEWITHARGS_H_
#define ITESTCONCURRENTSTATEMACHINEWITHARGS_H_

#include "Region.h"
#include "EventArgs.h"

class TestConcurrentCompositeStateWithArgsMock;

class ITestConcurrentStateMachineWithArgs
{
public:
	typedef sttcl::RegionBase<TestConcurrentCompositeStateWithArgsMock,ITestConcurrentStateMachineWithArgs,EventArgs> RegionContext;

	virtual void handleEvent1(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent2(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent3(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent4(TestConcurrentCompositeStateWithArgsMock* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual ~ITestConcurrentStateMachineWithArgs() {}
};

#endif /* ITESTCONCURRENTSTATEMACHINEWITHARGS_H_ */
