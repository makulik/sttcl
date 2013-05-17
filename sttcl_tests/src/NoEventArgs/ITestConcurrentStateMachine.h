/*
 * ITestConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ITESTCONCURRENTSTATEMACHINE_H_
#define ITESTCONCURRENTSTATEMACHINE_H_

#include "Region.h"

template<unsigned int NestingLevel>
class TestConcurrentCompositeStateMock;

template<unsigned int NestingLevel>
class ITestConcurrentStateMachine
{
public:
	typedef sttcl::RegionBase<TestConcurrentCompositeStateMock<NestingLevel - 1>,ITestConcurrentStateMachine<NestingLevel> > RegionContext;
	typedef TestConcurrentCompositeStateMock<NestingLevel - 1> Context;

	virtual void handleEvent1(Context* context,RegionContext* regionContext) = 0;
	virtual void handleEvent2(Context* context,RegionContext* regionContext) = 0;
	virtual void handleEvent3(Context* context,RegionContext* regionContext) = 0;
	virtual void handleEvent4(Context* context,RegionContext* regionContext) = 0;
	virtual ~ITestConcurrentStateMachine() {}
};

#endif /* ITESTCONCURRENTSTATEMACHINE_H_ */
