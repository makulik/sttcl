///////////////////////////////////////////////////////////
//  RegionA.cpp
//  Implementation of the Class RegionA
//  Created on:      17-Jul-2012 22:48:03
//  Original author: Admin
///////////////////////////////////////////////////////////

#include "RegionA.h"
// Import Section Impl
#include "State4.h"

RegionA::RegionA(State3* regionContainer)
: RegionBaseClass(regionContainer)
{

}


RegionA::~RegionA(){

}

RegionA::InnerStateClass* RegionA::getInitialStateImpl() const {

	return &State4::getInstance();
}


void RegionA::handleEvent1(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
		RegionBaseClass::dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent1,eventArgs);
	}
	
}


void RegionA::handleEvent2(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
		RegionBaseClass::dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent2,eventArgs);
	}
	
}


void RegionA::handleEvent3(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
		RegionBaseClass::dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent3,eventArgs);
	}
	
}


void RegionA::handleEvent4(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
		RegionBaseClass::dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent4,eventArgs);
	}
	
}
