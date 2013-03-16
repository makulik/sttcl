///////////////////////////////////////////////////////////
//  DemoStateMachine.cpp
//  Implementation of the Class DemoStateMachine
//  Created on:      17-Jul-2012 22:48:01
//  Original author: Admin
///////////////////////////////////////////////////////////

// EA generated imports
#include "DemoStateMachine.h"
// Sttcl generated imports
#include "State2.h"
#include "State3.h"
#include "State1.h"

DemoStateMachine::DemoStateMachine()
: state2(new State2())
, state3(new State3(this))
{

}

DemoStateMachine::~DemoStateMachine(){
	delete state3;
	delete state2;
}

void DemoStateMachine::event1(int p1, std::string& p2){

	StateBaseClass* currentState = getState();
	if(currentState)
	{
	    currentState->handleEvent1(this,p1,p2);
	}
	
}


void DemoStateMachine::event2(double p1, double p2){

	StateBaseClass* currentState = getState();
	if(currentState)
	{
	    currentState->handleEvent2(this,p1,p2);
	}
	
}


void DemoStateMachine::event3(){

	StateBaseClass* currentState = getState();
	if(currentState)
	{
	    currentState->handleEvent3(this);
	}
	
}


void DemoStateMachine::event4(int p1, long p2, std::vector<int>& p3){

	StateBaseClass* currentState = getState();
	if(currentState)
	{
	    currentState->handleEvent4(this,p1,p2,p3);
	}
	
}


DemoStateMachine::StateBaseClass* DemoStateMachine::getInitialStateImpl() const {

	return &State1::getInstance();
	
}


State2& DemoStateMachine::getState2() const {

	return *state2;
}


State3& DemoStateMachine::getState3() const {

	return *state3;
}


int DemoStateMachine::getX(){

	return 0;
}


int DemoStateMachine::getY(){

	return 0;
}

int main(int argc, char* argv[])
{
	return 0;
}
