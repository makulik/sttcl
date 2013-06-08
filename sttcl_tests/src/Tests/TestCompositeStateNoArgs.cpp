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
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
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
    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
//    compositeState.enableLogging(true);
//    innerState.enableLogging(true);

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
//    compositeState.enableLogging(true);
//    innerState.enableLogging(true);

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
    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
        .Times(1);
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

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Resume1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState("compositeState");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState1("innerState1");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState2("innerState2");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState("outerState");
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState1);
    innerState1.setDirectTransitState(&innerState2);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(CompositeStateMockType, handleEvent1, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    EXPECT_CALL(outerState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent1, &outerState, &compositeState) );
    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&compositeState))
        .Times(1);
// Direct transition prevents initializing sub state machines
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState1,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState2,entryImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,startDoImpl(&compositeState))
        .Times(2);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(false))
//        .Times(1);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(true))
//        .Times(1);
    EXPECT_CALL(innerState2,endDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&compositeState))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------
//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.finalize(true);

//    STTCL_TEST_LOG_END();
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_ShallowHistory_Resume2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Shallow
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState("compositeState");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState1("innerState1");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState2("innerState2");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState("outerState");
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState1);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(CompositeStateMockType, handleEvent1, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    EXPECT_CALL(outerState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent2, &outerState, &compositeState) );
    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,initSubStateMachinesImpl(false))
        .Times(1);
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(true))
//        .Times(1);
    EXPECT_CALL(innerState1,handleEvent1(&compositeState))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<CompositeStateMockType>, handleEvent1, &innerState1, &innerState2) );
    EXPECT_CALL(innerState1,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&compositeState))
        .Times(1);

//    EXPECT_CALL(innerState2,entryImpl(&compositeState))
//        .Times(2);
    EXPECT_CALL(innerState2,startDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState2,endDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&compositeState))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.finalize(true);

//    STTCL_TEST_LOG_END();
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Interactions1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
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
//    compositeState.enableLogging(true);
//    innerState.enableLogging(true);

    stateMachine.initialize();
    stateMachine.finalize(false);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Interactions2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
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

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Interactions3)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
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
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
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

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Interactions4)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
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

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Resume1)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState1;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState2;
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState1);
    innerState1.setDirectTransitState(&innerState2);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(CompositeStateMockType, handleEvent1, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    EXPECT_CALL(outerState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent1, &outerState, &compositeState) );
    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&compositeState))
        .Times(1);
// Direct transition prevents initializing sub state machines
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState1,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState2,entryImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,startDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState2,endDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&compositeState))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.finalize(true);
}

TEST_F(TestCompositeStateNoArgs,BasicCompositeState_DeepHistory_Resume2)
{
    typedef TestCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            , sttcl::CompositeStateHistoryType::Deep
            > CompositeStateMockType;
    ::testing::NiceMock
        < CompositeStateMockType
        > compositeState("compositeState");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState1("innerState1");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<CompositeStateMockType>
        > innerState2("innerState2");
    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState("outerState");
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");

    stateMachine.autoFinalize(false);
    compositeState.initialState(&innerState1);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,entryImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,startDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(CompositeStateMockType, handleEvent1, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    EXPECT_CALL(outerState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent2, &outerState, &compositeState) );
    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1,entryImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,initSubStateMachinesImpl(false))
        .Times(1);
    EXPECT_CALL(innerState1,handleEvent1(&compositeState))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<CompositeStateMockType>, handleEvent1, &innerState1, &innerState2) );
    EXPECT_CALL(innerState1,endDoImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState2,entryImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,startDoImpl(&compositeState))
        .Times(2);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(false))
//        .Times(2);
    EXPECT_CALL(innerState2,endDoImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&compositeState))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.finalize(true);

//    STTCL_TEST_LOG_END();
}
