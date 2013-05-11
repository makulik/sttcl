/*
 * ITestInnerStateInterfaceWithArgs.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACEWITHARGS_H_
#define ITESTINNERSTATEINTERFACEWITHARGS_H_

class TestCompositeStateWithArgsMock;

class ITestInnerStateInterfaceWithArgs
{
public:
    typedef TestCompositeStateWithArgsMock Context;

    virtual void handleEvent1(TestCompositeStateWithArgsMock* context, int arg1, const std::string& arg2) = 0;
	virtual void handleEvent2(TestCompositeStateWithArgsMock* context, double arg1) = 0;
	virtual void handleEvent3(TestCompositeStateWithArgsMock* context) = 0;
	virtual void handleEvent4(TestCompositeStateWithArgsMock* context, int arg1) = 0;

	virtual ~ITestInnerStateInterfaceWithArgs() {}
};


#endif /* ITESTINNERSTATEINTERFACEWITHARGS_H_ */
