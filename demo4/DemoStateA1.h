/*
 * DemoStateA1.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEA1_H_
#define DEMOSTATEA1_H_

#include "State.h"
#include "RegionA.h"

namespace Application
{

class DemoStateA1
: public sttcl::State<DemoStateA1,RegionA,IConcurrentStateMachine>
{
public:
	DemoStateA1();
	virtual ~DemoStateA1();

	virtual void handleEvent1(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent2(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent3(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent4(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);

	void entryImpl(IConcurrentStateMachine::Context* context);
	void exitImpl(IConcurrentStateMachine::Context* context);

	static DemoStateA1& getInstance();
};

}

#endif /* DEMOSTATEA1_H_ */
