/*
 * ICompositeStateWithArgsHooks.h
 *
 *  Created on: Apr 24, 2013
 *      Author: user
 */

#ifndef ICOMPOSITESTATEWITHARGSHOOKS_H_
#define ICOMPOSITESTATEWITHARGSHOOKS_H_

#include "SttclCompositeStateWithArgsMock.h"
#include "IStateWithArgsHooks.h"

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class ICompositeStateWithArgsHooks
: public IStateWithArgsHooks<StateMachineContext>
{
public:
    typedef sttcl::StateBase<CompositeStateImpl,InnerStateInterface> InnerStateBaseClass;

    virtual InnerStateBaseClass* getInitialStateImpl() const = 0;

    virtual bool isReadyImpl() const = 0;

    virtual bool initializeImpl(bool force) = 0;

    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

    virtual void subStateMachineCompletedImpl() = 0;

    virtual void subStateMachineCompleted() = 0;

    virtual ~ICompositeStateWithArgsHooks() {}
};

#endif /* ICOMPOSITESTATEWITHARGSHOOKS_H_ */
