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
    void handleEvent1(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    void handleEvent2(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    void handleEvent3(StateMachineType* context, EventArgsPtr eventArgs) = 0;
    void handleEvent4(StateMachineType* context, EventArgsPtr eventArgs) = 0;
};


#endif /* ITESTCONCURRENTSTATEINTERFACEWITHARGS_H_ */
