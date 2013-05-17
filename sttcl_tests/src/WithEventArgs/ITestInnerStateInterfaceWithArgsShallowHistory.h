/*
 * ITestInnerStateInterfaceWithArgsShallowHistory.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_
#define ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_

class TestCompositeStateWithArgsShallowHistoryMock;

class ITestInnerStateInterfaceWithArgsShallowHistory
{
public:
    typedef TestCompositeStateWithArgsShallowHistoryMock Context;

    virtual void handleEvent1(TestCompositeStateWithArgsShallowHistoryMock* context, int arg1, const std::string& arg2) = 0;
	virtual void handleEvent2(TestCompositeStateWithArgsShallowHistoryMock* context, double arg1) = 0;
	virtual void handleEvent3(TestCompositeStateWithArgsShallowHistoryMock* context) = 0;
	virtual void handleEvent4(TestCompositeStateWithArgsShallowHistoryMock* context, int arg1) = 0;

	virtual ~ITestInnerStateInterfaceWithArgsShallowHistory() {}
};


#endif /* ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_ */
