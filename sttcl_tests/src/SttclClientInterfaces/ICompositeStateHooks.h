/*
 * ICompositeStateHooks.h
 *
 *  Created on: Apr 24, 2013
 *      Author: user
 */

#ifndef ICOMPOSITESTATEHOOKS_H_
#define ICOMPOSITESTATEHOOKS_H_

#include "SttclCompositeStateMock.h"
#include "IStateHooks.h"

template
    < class CompostiteStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class ICompositeStateHooks
: public IStateHooks<StateMachineContext>
{
public:
    typedef sttcl::StateBase<CompostiteStateImpl,InnerStateInterface> InnerStateBaseClass;

    virtual InnerStateBaseClass* getInitialStateImpl() const = 0;

    virtual bool isReadyImpl() const = 0;

    virtual bool initializeImpl(bool force) = 0;

    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

    virtual void subStateMachineCompletedImpl() = 0;

    virtual void subStateMachineCompleted() = 0;

    virtual ~ICompositeStateHooks() {}
};

#endif /* ICOMPOSITESTATEHOOKS_H_ */
