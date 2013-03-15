///////////////////////////////////////////////////////////
//  State8.cpp
//  Implementation of the Class State8
//  Created on:      17-Jul-2012 22:48:17
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State8.h"
// Sttcl generated imports
#include "State7.h"

State8::State8(){

}


State8::~State8(){

}


State8& State8::getInstance(){

	static State8 theInstance;
	return theInstance;
	
}


void State8::handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	RegionB* region = static_cast<RegionB*>(regionContext);
	sttcl::RefCountPtr<State3::Event1Args> event1Args(eventArgs);
	changeState(region,&(State7::getInstance()));
	
}


void State8::handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event2Args> event2Args(eventArgs);

}


void State8::handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event3Args> event3Args(eventArgs);

}


void State8::handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){
	sttcl::RefCountPtr<State3::Event4Args> event4Args(eventArgs);

}
