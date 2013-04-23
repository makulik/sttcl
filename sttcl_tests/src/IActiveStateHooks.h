/*
 * IStateHooks.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef IACTIVESTATEHOOKS_H_
#define IACTIVESTATEHOOKS_H_

#include <ActiveState.h>
#include "SttclStateMachineMock.h"
#include "IStateHooks.h"

class ITestStateInterface;

class IActiveStateHooks
: public IStateHooks
{
public:
    virtual void exitingDoActionImpl() = 0;
    virtual void joinDoActionThreadImpl() = 0;
    virtual void unblockDoActionImpl() = 0;

	virtual ~IActiveStateHooks() {}
};


#endif /* IACTIVESTATEHOOKS_H_ */
