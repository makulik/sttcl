/*
 * ITestStateInterfaceWithArgs.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTSTATEINTERFACEWITHARGS_H_
#define ITESTSTATEINTERFACEWITHARGS_H_

class SttclStateMachineWithArgsMock;

class ITestStateInterfaceWithArgs
{
public:
    typedef SttclStateMachineWithArgsMock Context;

	virtual void handleEvent1(SttclStateMachineWithArgsMock* context, int arg1, const std::string& arg2) = 0;
	virtual void handleEvent2(SttclStateMachineWithArgsMock* context, double arg1) = 0;
	virtual void handleEvent3(SttclStateMachineWithArgsMock* context) = 0;
	virtual void handleEvent4(SttclStateMachineWithArgsMock* context, int arg1) = 0;

	virtual ~ITestStateInterfaceWithArgs() {}
};


#endif /* ITESTSTATEINTERFACEWITHARGS_H_ */
