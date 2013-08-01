/*
 * Demo3aStateMachine.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */


#include "Demo3aStateMachine.h"
#include "DemoState3.h"

using namespace Demo3a;
using Demo3a::Demo3aStateMachine;

Demo3aStateMachine::Demo3aStateMachine()
: MockBaseClass()
, x_(0)
, y_(0)
, demoState1_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState1"))
, demoState2_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState2"))
, demoState3_(new ::testing::NiceMock<Demo3a::DemoState3>("DemoState3"))
{
    initialState(demoState1_.get());
}

Demo3aStateMachine::~Demo3aStateMachine()
{
}

Demo3a::DemoState3& Demo3aStateMachine::DemoState3()
{
    return *demoState3_;
}

Demo3aStateMachine::SimpleInnerStateType& Demo3aStateMachine::DemoState1()
{
    return *demoState1_;
}

Demo3aStateMachine::SimpleInnerStateType& Demo3aStateMachine::DemoState2()
{
    return *demoState2_;
}

void Demo3aStateMachine::triggerEvent1()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent1(this);
    }
}

void Demo3aStateMachine::triggerEvent2()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent2(this);
    }
}

void Demo3aStateMachine::triggerEvent3()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent3(this);
    }
}

void Demo3aStateMachine::triggerEvent4()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent4(this);
    }
}

void Demo3aStateMachine::triggerEvent5()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent5(this);
    }
}


