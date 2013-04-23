/*
 * IStateMachineHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ISTATEMACHINEHOOKS_H_
#define ISTATEMACHINEHOOKS_H_
#include <State.h>
#include "ITestStateInterface.h"

class SttclStateMachineMock;

class IStateMachineHooks
{
public:
	typedef sttcl::StateBase<SttclStateMachineMock,ITestStateInterface> StateBaseClass;

	virtual bool initializeImpl(bool force) = 0;
	virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;
	virtual void subStateMachineCompletedImpl(StateBaseClass* state) = 0;
    virtual StateBaseClass* getInitialStateImpl() const = 0;
    virtual bool isReadyImpl() const = 0;

	virtual ~IStateMachineHooks() {}
};


#endif /* ISTATEMACHINEHOOKS_H_ */
