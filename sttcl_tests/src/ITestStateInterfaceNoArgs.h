/*
 * ITestStateInterfaceNoArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTSTATEINTERFACENOARGS_H_
#define ITESTSTATEINTERFACENOARGS_H_

template<typename StateMachineType>
struct ITestStateInterfaceNoArgs
{
    virtual void handleEvent1(StateMachineType* context) = 0;
    virtual void handleEvent2(StateMachineType* context) = 0;
    virtual void handleEvent3(StateMachineType* context) = 0;
    virtual void handleEvent4(StateMachineType* context) = 0;

    virtual ~ITestStateInterfaceNoArgs() {}
};


#endif /* ITESTSTATEINTERFACENOARGS_H_ */
