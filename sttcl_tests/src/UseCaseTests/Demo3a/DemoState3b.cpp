/*
 * DemoState3b.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#include "DemoState3b.h"
#include "Demo3aStateMachine.h"
#include "DemoState3.h"

using Demo3a::DemoState3b;

DemoState3b::DemoState3b(const std::string& id)
: MockBase(id)
, demoState3b_1(new ::testing::NiceMock<DemoState3b::SimpleInnerStateType>("DemoState3b_1"))
, demoState3b_2(new ::testing::NiceMock<DemoState3b::SimpleInnerStateType>("DemoState3b_2"))
, demoState3b_3(new ::testing::NiceMock<DemoState3b::SimpleInnerStateType>("DemoState3b_3"))
{
    initialState(demoState3b_1.get());
}

DemoState3b::~DemoState3b()
{
}

DemoState3b::SimpleInnerStateType& DemoState3b::DemoState3b_1()
{
    return *demoState3b_1;
}

DemoState3b::SimpleInnerStateType& DemoState3b::DemoState3b_2()
{
    return *demoState3b_2;
}

DemoState3b::SimpleInnerStateType& DemoState3b::DemoState3b_3()
{
    return *demoState3b_3;
}
