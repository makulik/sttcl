/*
 * ITestInnerStateInterfaceDeepHistory.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACEDEEPHISTORY_H_
#define ITESTINNERSTATEINTERFACEDEEPHISTORY_H_

template<unsigned int NestingLevel>
class TestCompositeStateDeepHistoryMock;

template<unsigned int NestingLevel = 1>
class ITestInnerStateInterfaceDeepHistory
{
public:
    typedef TestCompositeStateDeepHistoryMock<NestingLevel - 1> Context;

    virtual void handleEvent1(Context* context) = 0;
	virtual void handleEvent2(Context* context) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context) = 0;

	virtual ~ITestInnerStateInterfaceDeepHistory() {}
};


#endif /* ITESTINNERSTATEINTERFACEDEEPHISTORY_H_ */
