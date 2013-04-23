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

class ITestStateInterface;

class IStateHooks
{
public:
	virtual void entryImpl(SttclStateMachineMock* context) = 0;
	virtual void exitImpl(SttclStateMachineMock* context) = 0;
	virtual void startDoImpl(SttclStateMachineMock* context) = 0;
	virtual void endDoImpl(SttclStateMachineMock* context) = 0;
	virtual void finalizeSubStateMachinesImpl(bool recursive) = 0;
	virtual void initSubStateMachinesImpl(bool recursive) = 0;
	virtual bool checkDirectTransitionImpl(SttclStateMachineMock* context, bool& finalize, sttcl::StateBase<SttclStateMachineMock,ITestStateInterface>*& nextState) = 0;
	virtual void doActionImpl(SttclStateMachineMock* context, bool firstCall) = 0;
    virtual void joinDoActionImpl(SttclStateMachineMock* context) = 0;

	virtual ~IStateHooks() {}
};


#endif /* ISTATEHOOKS_H_ */
