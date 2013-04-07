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

	virtual void handleEvent1(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent2(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent3(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);
	virtual void handleEvent4(ConcurrentStateMachine* context,IConcurrentStateMachine::RegionContext* regionContext,sttcl::RefCountPtr<Event> eventArgs);

	void entryImpl(IConcurrentStateMachine::RegionContext* regionContext);
	void exitImpl(IConcurrentStateMachine::RegionContext* regionContext);

	static DemoStateA2& getInstance();
};

}

#endif /* DEMOSTATEA2_H_ */
