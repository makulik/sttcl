/*
 * ITestInnerStateInterfaceWithArgsShallowHistory.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_
#define ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_

template<unsigned int NestingLevel>
class TestCompositeStateWithArgsShallowHistoryMock;

template<unsigned int NestingLevel = 1>
class ITestInnerStateInterfaceWithArgsShallowHistory
{
public:
    typedef TestCompositeStateWithArgsShallowHistoryMock<NestingLevel - 1> Context;

    virtual void handleEvent1(Context* context, int arg1, const std::string& arg2) = 0;
	virtual void handleEvent2(Context* context, double arg1) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context, int arg1) = 0;

	virtual ~ITestInnerStateInterfaceWithArgsShallowHistory() {}
};


#endif /* ITESTINNERSTATEINTERFACEWITHARGSSHALLOWHISTORY_H_ */
