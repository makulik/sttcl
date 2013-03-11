///////////////////////////////////////////////////////////
//  State5.cpp
//  Implementation of the Class State5
//  Created on:      17-Jul-2012 22:48:14
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State5.h"
// Sttcl generated imports
#include "State4.h"

State5::State5(){

}


State5::~State5(){

}


void State5::exitImpl(RegionA* region){
	// call base implementation
	StateBaseClass::exitImpl(region);
}


State5& State5::getInstance(){

	static State5 theInstance;
	return theInstance;
	
}


void State5::handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){
	sttcl::RefCountPtr<State3::Event1Args> event1Args(eventArgs);

}


void State5::handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){
	sttcl::RefCountPtr<State3::Event2Args> event2Args(eventArgs);

}


void State5::handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){
	RegionA* region = static_cast<RegionA*>(regionContext);
	sttcl::RefCountPtr<State3::Event3Args> event3Args(eventArgs);
	changeState(region,&(State4::getInstance()));
	
}


void State5::handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs){
	RegionA* region = static_cast<RegionA*>(regionContext);
	sttcl::RefCountPtr<State3::Event4Args> event4Args(eventArgs);
	region->finalize();
	
}
