/*
 * ITestInnerConcurrentStateInterfaceWithArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTINNERCONCURRENTSTATEINTERFACEWITHARGS_H_
#define ITESTINNERCONCURRENTSTATEINTERFACEWITHARGS_H_

#include "EventArgs.h"

template
    < typename StateMachineType
    , typename RegionContextType
    >
struct ITestInnerConcurrentStateInterfaceWithArgs
{
    void handleEvent1(StateMachineType* context, RegionContextType* regionContext, EventArgsPtr eventArgs) = 0;
    void handleEvent2(StateMachineType* context, RegionContextType* regionContext, EventArgsPtr eventArgs) = 0;
    void handleEvent3(StateMachineType* context, RegionContextType* regionContext, EventArgsPtr eventArgs) = 0;
    void handleEvent4(StateMachineType* context, RegionContextType* regionContext, EventArgsPtr eventArgs) = 0;
};


#endif /* ITESTINNERCONCURRENTSTATEINTERFACEWITHARGS_H_ */
