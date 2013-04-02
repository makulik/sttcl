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

	virtual void handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext);
	virtual void handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext);
	virtual void handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext);
	virtual void handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext);

	void entryImpl(IConcurrentStateMachine::RegionContext* regionContext);
	void exitImpl(IConcurrentStateMachine::RegionContext* regionContext);

	static DemoStateB1& getInstance();
};

}

#endif /* DEMOSTATEB1_H_ */
