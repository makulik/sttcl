/*
 * TestConcurrentCompositeStateWithArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestConcurrentCompositeStateMocks.h"
#include "TestStateMocks.h"
#include "TestRegionMocks.h"
#include "SttclTestActions.h"

class TestConcurrentCompositeStateWithArgs
: public ::testing::Test
{
public:
    TestConcurrentCompositeStateWithArgs()
    {
    }

    ~TestConcurrentCompositeStateWithArgs()
    {
    }
};

TEST_F(TestConcurrentCompositeStateWithArgs,Constructor1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
}

//TEST_F(TestConcurrentCompositeStateWithArgs,Constructor2)
//{
//    typedef TestConcurrentCompositeStateWithArgsMock
//            < TestStateMachineWithEventArgsMock
//            , 2
//            > ConcurrentCompositeStateMockType;
//    ::testing::NiceMock
//        < ConcurrentCompositeStateMockType
//        > compositeState;
//}

TEST_F(TestConcurrentCompositeStateWithArgs,DirectTransition1)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestConcurrentCompositeStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestSimpleStateWithArgsMock<TestStateMachineWithEventArgsMock>
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

TEST_F(TestConcurrentCompositeStateWithArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestConcurrentCompositeStateWithArgsMock<TestStateMachineWithEventArgsMock>
        > compositeState(&stateMachine);

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

TEST_F(TestConcurrentCompositeStateWithArgs,BasicConcurrentCompositeStateInteractions1)
{
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);

    ::testing::NiceMock
        < TestRegionWithArgsMock<ConcurrentCompositeStateMockType>
        > region(&compositeState);

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
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

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(1);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

//    STTCL_TEST_LOG_END();
}

TEST_F(TestConcurrentCompositeStateWithArgs,BasicConcurrentCompositeStateInteractions2)
{
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);

    ::testing::NiceMock
        < TestRegionWithArgsMock<ConcurrentCompositeStateMockType>
        > region(&compositeState);

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
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

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(1);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

//    STTCL_TEST_LOG_END();
}

TEST_F(TestConcurrentCompositeStateWithArgs,BasicConcurrentCompositeStateInteractions3)
{
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionWithArgsMock<ConcurrentCompositeStateMockType>
        > region(&compositeState);

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
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

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(3);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------

    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

    STTCL_TEST_LOG_END();
}

TEST_F(TestConcurrentCompositeStateWithArgs,BasicConcurrentCompositeStateInteractions4)
{
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionWithArgsMock<ConcurrentCompositeStateMockType>
        > region(&compositeState);

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
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

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(3);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

//    compositeState.enableLogging(true);
//    innerState.enableLogging(true);

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

//    STTCL_TEST_LOG_END();
}

TEST_F(TestConcurrentCompositeStateWithArgs,EventPropagation)
{
    typedef TestConcurrentCompositeStateWithArgsMock
            < TestStateMachineWithEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineWithEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionWithArgsMock<ConcurrentCompositeStateMockType>
        > region(&compositeState);

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
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

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(1);
    EXPECT_CALL(region,handleEvent1(&compositeState,&region,_))
        .Times(1);
    EXPECT_CALL(region,handleEvent2(&compositeState,&region,_))
        .Times(1);
    EXPECT_CALL(region,handleEvent3(&compositeState,&region,_))
        .Times(1);
    EXPECT_CALL(region,handleEvent4(&compositeState,&region,_))
        .Times(1);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

//    compositeState.enableLogging(true);
//    innerState.enableLogging(true);

    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.triggerEvent1("Hello!",42);
    stateMachine.triggerEvent2(3.1415);
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4(12345);
    stateMachine.finalize();

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

//    STTCL_TEST_LOG_END();
}
