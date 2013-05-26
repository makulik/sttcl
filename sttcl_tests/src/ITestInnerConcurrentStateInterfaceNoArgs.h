/*
 * ITestInnerConcurrentStateInterfaceNoArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_
#define ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_

template
    < typename StateMachineType
    , typename RegionContextType
    >
struct ITestInnerConcurrentStateInterfaceNoArgs
{
    void handleEvent1(StateMachineType* context, RegionContextType* regionContext) = 0;
    void handleEvent2(StateMachineType* context, RegionContextType* regionContext) = 0;
    void handleEvent3(StateMachineType* context, RegionContextType* regionContext) = 0;
    void handleEvent4(StateMachineType* context, RegionContextType* regionContext) = 0;
};


#endif /* ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_ */
