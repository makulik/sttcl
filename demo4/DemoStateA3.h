/*
 * DemoStateA3.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEA3_H_
#define DEMOSTATEA3_H_

#include "State.h"
#include "RegionA.h"

namespace Application
{

class DemoStateA3
: public sttcl::State<DemoStateA3,RegionA,IConcurrentStateMachine>
{
public:
	DemoStateA3();
	virtual ~DemoStateA3();

	virtual void handleEvent1(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent2(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent3(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);
	virtual void handleEvent4(IConcurrentStateMachine::Context* context,const void* eventArgs = 0);

	void entryImpl(IConcurrentStateMachine::Context* context);
	void exitImpl(IConcurrentStateMachine::Context* context);

	static DemoStateA3& getInstance();
};

}

#endif /* DEMOSTATEA3_H_ */
