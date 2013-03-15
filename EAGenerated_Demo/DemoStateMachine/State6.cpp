///////////////////////////////////////////////////////////
//  State6.cpp
//  Implementation of the Class State6
//  Created on:      17-Jul-2012 22:48:15
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State6.h"
// Sttcl generated imports
#include "State8.h"

State6::State6(){

}


State6::~State6(){

}


State6& State6::getInstance(){

	static State6 theInstance;
	return theInstance;
	
}


void State6::handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	sttcl::RefCountPtr<State3::Event1Args> event1Args(eventArgs);


}


void State6::handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	RegionB* region = static_cast<RegionB*>(regionContext);
	sttcl::RefCountPtr<State3::Event2Args> event2Args(eventArgs);

	changeState(region,&(State8::getInstance()));
	
}


void State6::handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	sttcl::RefCountPtr<State3::Event3Args> event3Args(eventArgs);


}


void State6::handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs){

	sttcl::RefCountPtr<State3::Event4Args> event4Args(eventArgs);


}
