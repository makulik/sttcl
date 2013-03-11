///////////////////////////////////////////////////////////
//  State2.cpp
//  Implementation of the Class State2
//  Created on:      17-Jul-2012 22:48:07
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "State2.h"
// Sttcl generated imports
#include "State1.h"
#include "State9.h"

State2::State2()
: StateBaseClass(&State2::doAction,false,sttcl::TimeDuration<>(0,0,1))
{

}


State2::~State2(){

}


bool State2::checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState){

	if(context->getX() > 20)
	{
	    nextState = &(State1::getInstance());
	    return true;
	}
	else
	{
	    nextState = &(State9::getInstance());
	    return true;
	}
	
	return false;
	
}


void State2::doAction(DemoStateMachine* context, bool initialCall){

}


void State2::handleEvent1(DemoStateMachine* context, int p1, std::string& p2){

}


void State2::handleEvent2(DemoStateMachine* context, double p1, double p2){

}


void State2::handleEvent3(DemoStateMachine* context){

}


void State2::handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3){

	changeState(context,&(State1::getInstance()));
	
}


int State2::Z(){

	return 0;
}
