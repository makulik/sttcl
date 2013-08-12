/*
 * Demo3StateMachine.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */


#include "Demo3StateMachine.h"
#include "DemoState3.h"

using namespace Demo3;
using Demo3::Demo3StateMachine;

Demo3StateMachine::Demo3StateMachine()
: MockBaseClass()
, x_(0)
, y_(0)
, demoState1_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState1"))
, demoState2_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState2"))
, demoState3_(new ::testing::NiceMock<Demo3::DemoState3>("DemoState3"))
{
    initialState(demoState1_.get());
}

Demo3StateMachine::~Demo3StateMachine()
{
}

Demo3::DemoState3& Demo3StateMachine::DemoState3()
{
    return *demoState3_;
}

Demo3StateMachine::SimpleInnerStateType& Demo3StateMachine::DemoState1()
{
    return *demoState1_;
}

Demo3StateMachine::SimpleInnerStateType& Demo3StateMachine::DemoState2()
{
    return *demoState2_;
}

void Demo3StateMachine::triggerEvent1()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent1(this);
    }
}

void Demo3StateMachine::triggerEvent2()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent2(this);
    }
}

void Demo3StateMachine::triggerEvent3()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent3(this);
    }
}

void Demo3StateMachine::triggerEvent4()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent4(this);
    }
}

void Demo3StateMachine::triggerEvent5()
{
    StateBaseClass* currentState = MockBaseClass::getState();
    if(currentState)
    {
        currentState->handleEvent5(this);
    }
}


