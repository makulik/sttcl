///////////////////////////////////////////////////////////
//  RegionB.cpp
//  Implementation of the Class RegionB
//  Created on:      17-Jul-2012 22:48:04
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "RegionB.h"
// Sttcl generated imports
#include "State6.h"

RegionB::RegionB(State3* regionContainer)
: RegionBaseClass(regionContainer)
{

}


RegionB::~RegionB(){

}


RegionB::InnerStateClass* RegionB::getInitialStateImpl() const {

	return &State6::getInstance();
	
}


void RegionB::handleEvent1(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
	    dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent1,eventArgs);
	}
	
}


void RegionB::handleEvent2(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
	    dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent2,eventArgs);
	}
	
}


void RegionB::handleEvent3(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
	    dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent3,eventArgs);
	}
	
}


void RegionB::handleEvent4(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	InnerStateClass* currentState = getState();
	if(currentState)
	{
	    dispatchEvent(context,currentState,&State3_IInnerEvents::handleEvent4,eventArgs);
	}
	
}
