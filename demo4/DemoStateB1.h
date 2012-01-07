/*
 * DemoStateB1.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEB1_H_
#define DEMOSTATEB1_H_

#include "State.h"
#include "RegionB.h"

namespace Application
{

class DemoStateB1
: public sttcl::State<DemoStateB1,RegionB,IConcurrentStateMachine>
{
public:
	DemoStateB1();
	virtual ~DemoStateB1();

	virtual void handleEvent1(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent2(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent3(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent4(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);

	void entryImpl(IConcurrentStateMachine::Context* context);
	void exitImpl(IConcurrentStateMachine::Context* context);

	static DemoStateB1& getInstance();
};

}

#endif /* DEMOSTATEB1_H_ */
