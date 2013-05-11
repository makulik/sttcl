/*
 * IConcurrentCompositeStateHooks.h
 *
 *  Created on: Apr 24, 2013
 *      Author: user
 */

#ifndef ICONCURRENTCOMPOSITESTATEHOOKS_H_
#define ICONCURRENTCOMPOSITESTATEHOOKS_H_

#include "IStateHooks.h"
#include <Region.h>

template
    < class CompositeStateImpl
    , class StateMachineContext
    , class InnerStateInterface
    >
class IConcurrentCompositeStateHooks
: public IStateHooks<StateMachineContext>
{
public:
    typedef sttcl::StateBase<CompositeStateImpl,InnerStateInterface> InnerStateBaseClass;
    typedef sttcl::RegionBase<CompositeStateImpl,InnerStateInterface> RegionBaseClass;

    virtual bool initializeImpl(bool force) = 0;

    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

//    virtual void subStateMachineCompletedImpl() = 0;
//
//    virtual void subStateMachineCompleted() = 0;

    virtual void regionCompletedImpl(RegionBaseClass* region) = 0;

    virtual ~IConcurrentCompositeStateHooks() {}
};

#endif /* ICONCURRENTCOMPOSITESTATEHOOKS_H_ */
