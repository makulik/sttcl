/*
 * IStateWithArgsHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ISTATEWITHARGSHOOKS_H_
#define ISTATEWITHARGSHOOKS_H_

#include <State.h>
#include "SttclStateMachineWithArgsMock.h"

template<class StateMachineContext>
class IStateWithArgsHooks
{
public:
	virtual void entryImpl(StateMachineContext* context) = 0;
	virtual void exitImpl(StateMachineContext* context) = 0;
	virtual void startDoImpl(StateMachineContext* context) = 0;
	virtual void endDoImpl(StateMachineContext* context) = 0;
	virtual void finalizeSubStateMachinesImpl(bool recursive) = 0;
	virtual void initSubStateMachinesImpl(bool recursive) = 0;
	virtual bool checkDirectTransitionImpl(StateMachineContext* context, bool& finalize, sttcl::StateBase<StateMachineContext,typename StateMachineContext::StateInterface>*& nextState) = 0;
	virtual void doActionImpl(StateMachineContext* context, bool firstCall) = 0;
    virtual void joinDoActionImpl(StateMachineContext* context) = 0;

	virtual ~IStateWithArgsHooks() {}
};


#endif /* ISTATEWITHARGSHOOKS_H_ */
