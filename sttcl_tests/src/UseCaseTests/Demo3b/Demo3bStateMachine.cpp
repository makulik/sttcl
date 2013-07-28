/*
 * Demo3bStateMachine.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */


#include "Demo3bStateMachine.h"
#include "DemoState3.h"

using namespace Demo3b;
using Demo3b::Demo3bStateMachine;

Demo3bStateMachine::Demo3bStateMachine()
: MockBaseClass()
, x_(0)
, y_(0)
, demoState1_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState1"))
, demoState2_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState2"))
, demoState3_(new ::testing::NiceMock<Demo3b::DemoState3>("DemoState3"))
{
    initialState(demoState1_.get());
}

Demo3bStateMachine::~Demo3bStateMachine()
{
}

Demo3b::DemoState3& Demo3bStateMachine::DemoState3()
{
    return *demoState3_;
}

Demo3bStateMachine::SimpleInnerStateType& Demo3bStateMachine::DemoState1()
{
    return *demoState1_;
}

Demo3bStateMachine::SimpleInnerStateType& Demo3bStateMachine::DemoState2()
{
    return *demoState2_;
}

void Demo3bStateMachine::triggerEvent1()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent1(this);
    }
}

void Demo3bStateMachine::triggerEvent2()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent2(this);
    }
}

void Demo3bStateMachine::triggerEvent3()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent3(this);
    }
}

void Demo3bStateMachine::triggerEvent4()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent4(this);
    }
}

void Demo3bStateMachine::triggerEvent5()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent5(this);
    }
}


