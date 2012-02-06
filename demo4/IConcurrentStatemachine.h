/*
 * IConcurrentStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef ICONCURRENTSTATEMACHINE_H_
#define ICONCURRENTSTATEMACHINE_H_

#include "Region.h"
#include "IDemoState.h"

namespace Application
{

class DemoStateMachine;

class IConcurrentStateMachine
{
public:
	typedef sttcl::RegionBase<DemoStateMachine,IDemoState> Context;

	virtual void handleEvent1(Context* context,const void* eventArgs = 0) = 0;
	virtual void handleEvent2(Context* context,const void* eventArgs = 0) = 0;
	virtual void handleEvent3(Context* context,const void* eventArgs = 0) = 0;
	virtual void handleEvent4(Context* context,const void* eventArgs = 0) = 0;
	virtual ~IConcurrentStateMachine() {}
};

}

#endif /* ICONCURRENTSTATEMACHINE_H_ */
