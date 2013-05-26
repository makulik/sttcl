/*
 * ITestStateInterfaceWithArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTSTATEINTERFACEWITHARGS_H_
#define ITESTSTATEINTERFACEWITHARGS_H_

template<typename StateMachineType>
struct ITestStateInterfaceWithArgs
{
    virtual void handleEvent1(StateMachineType* context, const std::string& arg1, int arg2) = 0;
    virtual void handleEvent2(StateMachineType* context, double arg1) = 0;
    virtual void handleEvent3(StateMachineType* context) = 0;
    virtual void handleEvent4(StateMachineType* context, int arg1) = 0;
};


#endif /* ITESTSTATEINTERFACEWITHARGS_H_ */
