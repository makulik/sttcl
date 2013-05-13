/*
 * ITestInnerStateInterfaceShallowHistory.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_
#define ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_

class TestCompositeStateShallowHistoryMock;

class ITestInnerStateInterfaceShallowHistory
{
public:
    typedef TestCompositeStateShallowHistoryMock Context;

    virtual void handleEvent1(TestCompositeStateShallowHistoryMock* context) = 0;
	virtual void handleEvent2(TestCompositeStateShallowHistoryMock* context) = 0;
	virtual void handleEvent3(TestCompositeStateShallowHistoryMock* context) = 0;
	virtual void handleEvent4(TestCompositeStateShallowHistoryMock* context) = 0;

	virtual ~ITestInnerStateInterfaceShallowHistory() {}
};


#endif /* ITESTINNERSTATEINTERFACESHALLOWHISTORY_H_ */
