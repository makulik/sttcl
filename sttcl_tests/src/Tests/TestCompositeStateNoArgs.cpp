/*
 * TestCompositeStateNoArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestCompositeStateMocks.h"
#include "TestStateMocks.h"
#include "SttclTestActions.h"

class TestCompositeStateNoArgs
: public ::testing::Test
{
public:
    TestCompositeStateNoArgs()
    {
    }

    ~TestCompositeStateNoArgs()
    {
    }
};

TEST_F(TestCompositeStateNoArgs,Constructor1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::None
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
}

TEST_F(TestCompositeStateNoArgs,Constructor2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
}

TEST_F(TestCompositeStateNoArgs,Constructor3)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
}

TEST_F(TestCompositeStateNoArgs,DirectTransition1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestCompositeStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > state;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&compositeState);
    compositeState.setDirectTransitState(&state);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,checkDirectTransitionImpl(_,_,_))
        .Times(1);

    EXPECT_CALL(state,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state,finalizeSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(state,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(state,exitImpl(&stateMachine))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestCompositeStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > compositeState;

    stateMachine.autoFinalize(false);
    stateMachine.initialState(&compositeState);
    compositeState.finalizeOnNextDirectTransit();

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,checkDirectTransitionImpl(_,_,_))
        .Times(1);
    EXPECT_CALL(stateMachine,finalizeImpl(_))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeStateInteractions1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::None
            > CompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(false);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeStateInteractions2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::None
            > CompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeStateInteractions3)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::None
            > CompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(false);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeStateInteractions4)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::None
            > CompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Interactions1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    compositeState.enableLogging(true);
    innerState.enableLogging(true);

    stateMachine.initialize();
    stateMachine.finalize(false);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Interactions2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Interactions3)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(false);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Interactions4)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&compositeState))
        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.finalize(true);
}

