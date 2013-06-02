/*
 * ITestConcurrentStateInterfaceWithArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTCONCURRENTSTATEINTERFACEWITHARGS_H_
#define ITESTCONCURRENTSTATEINTERFACEWITHARGS_H_

#include "EventArgs.h"

template<typename StateMachineType>
struct ITestConcurrentStateInterfaceWithArgs
{
    virtual void handleEvent1(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    virtual void handleEvent2(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    virtual void handleEvent3(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    virtual void handleEvent4(StateMachineType* context, EventArgsPtr eventArgs) = 0;
};


#endif /* ITESTCONCURRENTSTATEINTERFACEWITHARGS_H_ */
