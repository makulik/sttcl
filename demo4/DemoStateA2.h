/*
 * DemoStateA2.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEA2_H_
#define DEMOSTATEA2_H_

#include "State.h"
#include "RegionA.h"

namespace Application
{

class DemoStateA2
: public sttcl::State<DemoStateA2,RegionA,IConcurrentStateMachine>
{
public:
	DemoStateA2();
	virtual ~DemoStateA2();

	virtual void handleEvent1(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent2(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent3(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent4(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);

	void entryImpl(IConcurrentStateMachine::Context* context);
	void exitImpl(IConcurrentStateMachine::Context* context);

	static DemoStateA2& getInstance();
};

}

#endif /* DEMOSTATEA2_H_ */
