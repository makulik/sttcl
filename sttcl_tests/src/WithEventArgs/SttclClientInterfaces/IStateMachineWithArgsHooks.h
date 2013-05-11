/*
 * IStateMachineWithArgsHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ISTATEMACHINEWITHARGSHOOKS_H_
#define ISTATEMACHINEWITHARGSHOOKS_H_
#include <State.h>
#include "ITestStateInterfaceWithArgs.h"

class SttclStateMachineWithArgsMock;

template <class StateInterface>
class IStateMachineWithArgsHooks
{
public:
	typedef sttcl::StateBase<SttclStateMachineWithArgsMock,StateInterface> StateBaseClass;

	virtual bool initializeImpl(bool force) = 0;
	virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;
	virtual void subStateMachineCompletedImpl(StateBaseClass* state) = 0;
    virtual StateBaseClass* getInitialStateImpl() const = 0;
    virtual bool isReadyImpl() const = 0;

	virtual ~IStateMachineWithArgsHooks() {}
};


#endif /* ISTATEMACHINEWITHARGSHOOKS_H_ */
