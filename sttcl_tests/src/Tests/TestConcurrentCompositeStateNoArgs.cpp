/*
 * TestConcurrentCompositeStateNoArgs.cpp
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

class TestConcurrentCompositeStateNoArgs
: public ::testing::Test
{
public:
    TestConcurrentCompositeStateNoArgs()
    {
    }

    ~TestConcurrentCompositeStateNoArgs()
    {
    }
};

TEST_F(TestConcurrentCompositeStateNoArgs,Constructor1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
}

//TEST_F(TestConcurrentCompositeStateNoArgs,Constructor2)
//{
//    typedef TestConcurrentCompositeStateNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , 2
//            > ConcurrentCompositeStateMockType;
//    ::testing::NiceMock
//        < ConcurrentCompositeStateMockType
//        > compositeState;
//}

TEST_F(TestConcurrentCompositeStateNoArgs,DirectTransition1)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestConcurrentCompositeStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > compositeState(&stateMachine);
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

TEST_F(TestConcurrentCompositeStateNoArgs,DirectTransition2)
{
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < TestConcurrentCompositeStateNoArgsMock<TestStateMachineNoEventArgsMock>
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

TEST_F(TestConcurrentCompositeStateNoArgs,BasicConcurrentCompositeStateInteractions1)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);

    ::testing::NiceMock
        < TestRegionNoArgsMock<ConcurrentCompositeStateMockType>
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

TEST_F(TestConcurrentCompositeStateNoArgs,BasicConcurrentCompositeStateInteractions2)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);

    ::testing::NiceMock
        < TestRegionNoArgsMock<ConcurrentCompositeStateMockType>
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

TEST_F(TestConcurrentCompositeStateNoArgs,BasicConcurrentCompositeStateInteractions3)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionNoArgsMock<ConcurrentCompositeStateMockType>
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

TEST_F(TestConcurrentCompositeStateNoArgs,BasicConcurrentCompositeStateInteractions4)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionNoArgsMock<ConcurrentCompositeStateMockType>
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

TEST_F(TestConcurrentCompositeStateNoArgs,EventPropagation)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < TestRegionNoArgsMock<ConcurrentCompositeStateMockType>
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
    EXPECT_CALL(region,handleEvent1(&compositeState,&region))
        .Times(1);
    EXPECT_CALL(region,handleEvent2(&compositeState,&region))
        .Times(1);
    EXPECT_CALL(region,handleEvent3(&compositeState,&region))
        .Times(1);
    EXPECT_CALL(region,handleEvent4(&compositeState,&region))
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
    stateMachine.triggerEvent1();
    stateMachine.triggerEvent2();
    stateMachine.triggerEvent3();
    stateMachine.triggerEvent4();
    stateMachine.finalize();

    EXPECT_TRUE(region.waitForDoActionExited(sttcl::TimeDuration<>(0,0,0,100),10));

//    STTCL_TEST_LOG_END();
}
