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

	virtual void handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);

	void entryImpl(IConcurrentStateMachine::RegionContext* regionContext);
	void exitImpl(IConcurrentStateMachine::RegionContext* regionContext);

	static DemoStateA3& getInstance();
};

}

#endif /* DEMOSTATEA3_H_ */
