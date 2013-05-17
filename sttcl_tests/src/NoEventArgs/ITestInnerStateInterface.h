/*
 * ITestInnerStateInterface.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACE_H_
#define ITESTINNERSTATEINTERFACE_H_

template<unsigned int NestingLevel>
class TestCompositeStateMock;

template<unsigned int NestingLevel = 1>
class ITestInnerStateInterface
{
public:
    typedef TestCompositeStateMock<NestingLevel -1> Context;

    virtual void handleEvent1(Context* context) = 0;
	virtual void handleEvent2(Context* context) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context) = 0;

	virtual ~ITestInnerStateInterface() {}
};


#endif /* ITESTINNERSTATEINTERFACE_H_ */
