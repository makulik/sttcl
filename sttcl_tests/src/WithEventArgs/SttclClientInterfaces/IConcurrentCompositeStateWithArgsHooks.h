/*
 * IConcurrentCompositeStateWithArgsHooks.h
 *
 *  Created on: Apr 24, 2013
 *      Author: user
 */

#ifndef ICONCURRENTCOMPOSITESTATEWITHARGSHOOKS_H_
#define ICONCURRENTCOMPOSITESTATEWITHARGSHOOKS_H_

#include "IStateWithArgsHooks.h"
#include <Region.h>

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class IConcurrentCompositeStateWithArgsHooks
: public IStateWithArgsHooks<StateMachineContext>
{
public:
    typedef sttcl::StateBase<CompositeStateImpl,InnerStateInterface> InnerStateBaseClass;
    typedef sttcl::RegionBase<CompositeStateImpl,InnerStateInterface,EventArgs> RegionBaseClass;

    virtual bool initializeImpl(bool force) = 0;

    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

//    virtual void subStateMachineCompletedImpl() = 0;
//
//    virtual void subStateMachineCompleted() = 0;

    virtual void regionCompletedImpl(RegionBaseClass* region) = 0;

    virtual ~IConcurrentCompositeStateWithArgsHooks() {}
};

#endif /* ICONCURRENTCOMPOSITESTATEHOOKS_H_ */
