/*
 * ITestConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ITESTCONCURRENTSTATEMACHINE_H_
#define ITESTCONCURRENTSTATEMACHINE_H_

#include "Region.h"

class TestConcurrentCompositeStateMock;

class ITestConcurrentStateMachine
{
public:
	typedef sttcl::RegionBase<TestConcurrentCompositeStateMock,ITestConcurrentStateMachine> RegionContext;

	virtual void handleEvent1(TestConcurrentCompositeStateMock* context,RegionContext* regionContext) = 0;
	virtual void handleEvent2(TestConcurrentCompositeStateMock* context,RegionContext* regionContext) = 0;
	virtual void handleEvent3(TestConcurrentCompositeStateMock* context,RegionContext* regionContext) = 0;
	virtual void handleEvent4(TestConcurrentCompositeStateMock* context,RegionContext* regionContext) = 0;
	virtual ~ITestConcurrentStateMachine() {}
};

#endif /* ITESTCONCURRENTSTATEMACHINE_H_ */
