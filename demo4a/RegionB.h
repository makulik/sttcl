/*
 * RegionB.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGIONB_H_
#define REGIONB_H_

#include "Region.h"
#include "IConcurrentStatemachine.h"
#include "DemoStateMachine.h"

namespace Application
{

class DemoStateMachine;

class RegionB
: public sttcl::Region<RegionB,DemoStateMachine,IConcurrentStateMachine,EventArgsClass>
{
public:
	typedef sttcl::Region<RegionB,DemoStateMachine,IConcurrentStateMachine,EventArgsClass> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	RegionB();
	virtual ~RegionB();

	virtual void handleEvent1(IDemoState::Context* context,sttcl::EventArgsPtr<EventArgsClass> eventArgs);
	virtual void handleEvent2(IDemoState::Context* context,sttcl::EventArgsPtr<EventArgsClass> eventArgs);
	virtual void handleEvent3(IDemoState::Context* context,sttcl::EventArgsPtr<EventArgsClass> eventArgs);
	virtual void handleEvent4(IDemoState::Context* context,sttcl::EventArgsPtr<EventArgsClass> eventArgs);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

	void startingRegionThread();
	void endingRegionThread();

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	InnerStateClass* getInitialStateImpl() const;

};

}

#endif /* REGIONB_H_ */
