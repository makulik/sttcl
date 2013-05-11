/*
 * IStateHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ISTATEHOOKS_H_
#define ISTATEHOOKS_H_

#include <State.h>
#include "SttclStateMachineMock.h"

template<class StateMachineContext>
class IStateHooks
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

	virtual ~IStateHooks() {}
};


#endif /* ISTATEHOOKS_H_ */
