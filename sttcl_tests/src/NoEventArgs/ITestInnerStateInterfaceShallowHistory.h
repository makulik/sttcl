/*
 * ITestInnerStateInterfaceShallowHistory.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_
#define ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_

template<unsigned int NestingLevel>
class TestCompositeStateShallowHistoryMock;

template<unsigned int NestingLevel = 1>
class ITestInnerStateInterfaceShallowHistory
{
public:
    typedef TestCompositeStateShallowHistoryMock<NestingLevel -1> Context;

    virtual void handleEvent1(Context* context) = 0;
	virtual void handleEvent2(Context* context) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context) = 0;

	virtual ~ITestInnerStateInterfaceShallowHistory() {}
};


#endif /* ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_ */
