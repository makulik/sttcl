/*
 * ITestInnerStateInterface.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACE_H_
#define ITESTINNERSTATEINTERFACE_H_

class TestCompositeStateMock;

class ITestInnerStateInterface
{
public:
    typedef TestCompositeStateMock Context;

    virtual void handleEvent1(TestCompositeStateMock* context) = 0;
	virtual void handleEvent2(TestCompositeStateMock* context) = 0;
	virtual void handleEvent3(TestCompositeStateMock* context) = 0;
	virtual void handleEvent4(TestCompositeStateMock* context) = 0;

	virtual ~ITestInnerStateInterface() {}
};


#endif /* ITESTINNERSTATEINTERFACE_H_ */
