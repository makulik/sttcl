///////////////////////////////////////////////////////////
//  State7.cpp
//  Implementation of the Class State7
//  Created on:      17-Jul-2012 22:48:16
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State7.h"
// Sttcl generated imports
#include "State6.h"

State7::State7(){

}


State7::~State7(){

}


State7& State7::getInstance(){

	static State7 theInstance;
	return theInstance;
	
}


void State7::handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	RegionB* region = static_cast<RegionB*>(regionContext);
	sttcl::RefCountPtr<State3::Event1Args> event1Args(eventArgs);

	if(context->context()->getX() < 4)
	{
	    region->finalize();
	}
	
}


void State7::handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	RegionB* region = static_cast<RegionB*>(regionContext);
	sttcl::RefCountPtr<State3::Event2Args> event2Args(eventArgs);

	if(context->context()->getX() < 4)
	{
	    region->finalize();
	}
}


void State7::handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event3Args> event3Args(eventArgs);

}


void State7::handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	RegionB* region = static_cast<RegionB*>(regionContext);
	sttcl::RefCountPtr<State3::Event4Args> event4Args(eventArgs);
	changeState(region,&(State6::getInstance()));
	
}
