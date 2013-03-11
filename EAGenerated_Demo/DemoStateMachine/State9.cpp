///////////////////////////////////////////////////////////
//  State9.cpp
//  Implementation of the Class State9
//  Created on:      17-Jul-2012 22:48:18
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State9.h"
// Sttcl generated imports

State9::State9(){

}


State9::~State9(){

}


bool State9::checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState){

	finalize = true;
	return true;
	
}


State9& State9::getInstance(){

	static State9 theInstance;
	return theInstance;
	
}


void State9::handleEvent1(DemoStateMachine* context, int p1, std::string& p2){

}


void State9::handleEvent2(DemoStateMachine* context, double p1, double p2){

}


void State9::handleEvent3(DemoStateMachine* context){

}


void State9::handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3){

}
