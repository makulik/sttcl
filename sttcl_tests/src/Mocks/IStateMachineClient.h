/*
 * IStateMachineClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ISTATEMACHINECLIENT_H_
#define ISTATEMACHINECLIENT_H_

template
    < typename StateMachineType
    , typename StateBaseClass
    >
struct IStateMachineClient
{
    virtual bool isReadyImpl() const = 0;
    virtual bool initializeImpl(bool force) = 0;
    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;
    virtual void subStateMachineCompletedImpl(StateBaseClass* state) = 0;
    virtual StateBaseClass* getInitialStateImpl() const = 0;

    virtual ~IStateMachineClient() {}
};


#endif /* ISTATEMACHINECLIENT_H_ */
