/*
 * IActiveStateWithArgsHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef IACTIVESTATEWITHARGSHOOKS_H_
#define IACTIVESTATEWITHARGSHOOKS_H_

#include <ActiveState.h>
#include "SttclStateMachineMock.h"
#include "IStateHooks.h"

class ITestStateInterface;

template<class StateMachineContext>
class IActiveStateWithArgsHooks
: public IStateHooks<StateMachineContext>
{
public:
    virtual void exitingDoActionImpl() = 0;
    virtual void joinDoActionThreadImpl() = 0;
    virtual void unblockDoActionImpl() = 0;

	virtual ~IActiveStateWithArgsHooks() {}
};


#endif /* IACTIVESTATEWITHARGSHOOKS_H_ */
