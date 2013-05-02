/*
 * IRegionHooks.h
 *
 *  Created on: Apr 24, 2013
 *      Author: user
 */

#ifndef IREGIONHOOKS_H_
#define IREGIONHOOKS_H_

#include "SttclConcurrentCompositeStateMock.h"
#include "IStateHooks.h"

template
    < class RegionImpl
    , class RegionContainer
    , class InnerStateInterface
    >
class IRegionHooks
{
public:
    typedef sttcl::StateBase<RegionImpl,InnerStateInterface> InnerStateBaseClass;

    virtual InnerStateBaseClass* getInitialStateImpl() const = 0;
    virtual bool isReadyImpl() const = 0;
    virtual bool initializeImpl(bool force) = 0;
    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

    virtual void subStateMachineCompletedImpl() = 0;
    virtual void subStateMachineCompleted() = 0;

    virtual void entryImpl(RegionContainer* context) = 0;
    virtual void exitImpl(RegionContainer* context) = 0;
    virtual void startDoImpl(RegionContainer* context) = 0;
    virtual void endDoImpl(RegionContainer* context) = 0;
    virtual void finalizeSubStateMachinesImpl(bool recursive) = 0;
    virtual void initSubStateMachinesImpl(bool recursive) = 0;
    virtual void doActionImpl(RegionContainer* context, bool firstCall) = 0;
    virtual void joinDoActionThreadImpl() = 0;

    virtual ~IRegionHooks() {}
};

#endif /* IREGIONHOOKS_H_ */
