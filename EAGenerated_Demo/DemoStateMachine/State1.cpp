///////////////////////////////////////////////////////////
//  State1.cpp
//  Implementation of the Class State1
//  Created on:      17-Jul-2012 22:48:06
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State1.h"
// Sttcl generated imports
#include "State3.h"

State1::State1(){

}


State1::~State1(){

}


void State1::entryImpl(DemoStateMachine* context){
	// call base implementation
	StateBaseClass::entryImpl(context);
}


State1& State1::getInstance(){

	static State1 theInstance;
	return theInstance;
	
}


void State1::handleEvent1(DemoStateMachine* context, int p1, std::string& p2){

	changeState(context,&(context->getState3()));
	
}


void State1::handleEvent2(DemoStateMachine* context, double p1, double p2){

}


void State1::handleEvent3(DemoStateMachine* context){

}


void State1::handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3){

}
