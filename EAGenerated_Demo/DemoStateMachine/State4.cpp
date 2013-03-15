///////////////////////////////////////////////////////////
//  State4.cpp
//  Implementation of the Class State4
//  Created on:      17-Jul-2012 22:48:13
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State4.h"
// Sttcl generated imports
#include "State5.h"



State4::State4(){

}


State4::~State4(){

}


State4& State4::getInstance(){

	static State4 theInstance;
	return theInstance;
	
}


void State4::handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	RegionA* region = static_cast<RegionA*>(regionContext);
	sttcl::RefCountPtr<State3::Event1Args> event1Args(eventArgs);
	changeState(region,&(State5::getInstance()));
}


void State4::handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event2Args> event2Args(eventArgs);
}


void State4::handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event3Args> event3Args(eventArgs);
}


void State4::handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event4Args> event4Args(eventArgs);
}
