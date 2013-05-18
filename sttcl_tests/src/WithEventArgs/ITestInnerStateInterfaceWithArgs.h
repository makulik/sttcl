/*
 * ITestInnerStateInterfaceWithArgs.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTINNERSTATEINTERFACEWITHARGS_H_
#define ITESTINNERSTATEINTERFACEWITHARGS_H_

template<unsigned int NestingLevel>
class TestCompositeStateWithArgsMock;

template<unsigned int NestingLevel = 1>
class ITestInnerStateInterfaceWithArgs
{
public:
    typedef TestCompositeStateWithArgsMock<NestingLevel - 1> Context;

    virtual void handleEvent1(Context* context, int arg1, const std::string& arg2) = 0;
	virtual void handleEvent2(Context* context, double arg1) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context, int arg1) = 0;

	virtual ~ITestInnerStateInterfaceWithArgs() {}
};


#endif /* ITESTINNERSTATEINTERFACEWITHARGS_H_ */
