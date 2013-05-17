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

template<unsigned int NestingLevel>
class TestConcurrentCompositeStateWithArgsMock;

template<unsigned int NestingLevel>
class ITestConcurrentStateMachineWithArgs
{
public:
	typedef sttcl::RegionBase<TestConcurrentCompositeStateWithArgsMock<NestingLevel -1>,ITestConcurrentStateMachineWithArgs<NestingLevel>,EventArgs> RegionContext;
    typedef TestConcurrentCompositeStateWithArgsMock<NestingLevel - 1> Context;

	virtual void handleEvent1(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent2(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent3(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual void handleEvent4(Context* context,RegionContext* regionContext, EventArgsPtr eventArgs) = 0;
	virtual ~ITestConcurrentStateMachineWithArgs() {}
};

#endif /* ITESTCONCURRENTSTATEMACHINEWITHARGS_H_ */
