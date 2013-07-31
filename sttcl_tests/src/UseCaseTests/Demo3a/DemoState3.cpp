/*
 * DemoState3.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#include "DemoState3.h"
#include "Demo3aStateMachine.h"
#include "DemoState3b.h"

using namespace Demo3a;
using Demo3a::DemoState3;

DemoState3::DemoState3(const std::string& id)
: MockBaseClass(id)
, z_(0)
, demoState3a_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState3a"))
, demoState3b_(new ::testing::NiceMock<Demo3a::DemoState3b>("DemoState3b"))
, demoState3c_(new ::testing::NiceMock<SimpleInnerStateType>("DemoState3c"))
{
    initialState(demoState3a_.get());
}

DemoState3::~DemoState3()
{
}

DemoState3::SimpleInnerStateType& DemoState3::DemoState3a()
{
    return *demoState3a_;
}

Demo3a::DemoState3b& DemoState3::DemoState3b()
{
    return *demoState3b_;
}

DemoState3::SimpleInnerStateType& DemoState3::DemoState3c()
{
    return *demoState3c_;
}
