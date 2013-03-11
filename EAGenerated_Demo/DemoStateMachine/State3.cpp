///////////////////////////////////////////////////////////
//  State3.cpp
//  Implementation of the Class State3
//  Created on:      17-Jul-2012 22:48:10
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State3.h"
// Sttcl generated imports
#include "State1.h"
#include "State2.h"
#include "State9.h"
#include "RegionA.h"
#include "RegionB.h"

State3::State3(DemoStateMachine* context)
: State3::CompositeStateBase(context,regions)
, regionA(new RegionA(this))
, regionB(new RegionB(this))
{

	regions[0] = regionA;
	regions[1] = regionB;
	
}


State3::~State3(){

}


bool State3::checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState){

	if(context->getY() > 30)
	{
	    nextState = &(State9::getInstance());
	    return true;
	}
	
	return false;
	
}


void State3::handleEvent1(DemoStateMachine* context, int p1, std::string& p2){

	// First broadcast the event to the contained regions
	// Create & initialize dispatched event args
	sttcl::RefCountPtr<Event1Args> event1Args(new Event1Args());
	event1Args->p1 = p1;
	event1Args->p2 = p2;
	
	CompositeStateBase::broadcastEvent(this,&State3_IInnerEvents::handleEvent1,event1Args);
	// Then take on with the transitions
	
	
}


void State3::handleEvent2(DemoStateMachine* context, double p1, double p2){

	// First broadcast the event to the contained regions
	// Create & initialize dispatched event args
	sttcl::RefCountPtr<Event2Args> event2Args(new Event2Args());
	event2Args->p1 = p1;
	event2Args->p2 = p2;
	
	CompositeStateBase::broadcastEvent(this,&State3_IInnerEvents::handleEvent2,event2Args);
	// Then take on with the transitions
	CompositeStateBase::changeState(context,&(context->getState2()));
	
}


void State3::handleEvent3(DemoStateMachine* context){

	// First broadcast the event to the contained regions
	// Create & initialize dispatched event args
	sttcl::RefCountPtr<Event3Args> event3Args(new Event3Args());
	
	CompositeStateBase::broadcastEvent(this,&State3_IInnerEvents::handleEvent3,event3Args);
	// Then take on with the transitions
	CompositeStateBase::changeState(context,&(State1::getInstance()));
	
	
}


void State3::handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3){

	// First broadcast the event to the contained regions
	// Create & initialize dispatched event args
	sttcl::RefCountPtr<Event4Args> event4Args(new Event4Args());
	event4Args->p1 = p1;
	event4Args->p2 = p2;
	event4Args->p3 = p3;
	
	CompositeStateBase::broadcastEvent(this,&State3_IInnerEvents::handleEvent4,event4Args);
	// Then take on with the transitions
	context->finalize();
	
	
}





State3::Event1Args::Event1Args(){

}


State3::Event1Args::~Event1Args(){

}


State3::Event2Args::Event2Args(){

}


State3::Event2Args::~Event2Args(){

}


State3::Event3Args::Event3Args(){

}


State3::Event3Args::~Event3Args(){

}


State3::Event4Args::Event4Args(){

}


State3::Event4Args::~Event4Args(){

}
