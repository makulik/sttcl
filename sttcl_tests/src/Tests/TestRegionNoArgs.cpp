/*
 * TestRegionNoArgs.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TestStateMachineMocks.h"
#include "TestConcurrentCompositeStateMocks.h"
#include "TestRegionMocks.h"
#include "TestStateMocks.h"
#include "TestRegionInnerStateMocks.h"
#include "SttclTestActions.h"

class TestRegionNoArgs
: public ::testing::Test
{
public:
    TestRegionNoArgs()
    {
    }

    ~TestRegionNoArgs()
    {
    }
};

TEST_F(TestRegionNoArgs,Constructor1)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::None
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
}

TEST_F(TestRegionNoArgs,Constructor2)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
}

TEST_F(TestRegionNoArgs,Constructor3)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Deep
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
}

TEST_F(TestRegionNoArgs,BasicRegionInteractions1)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::None
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
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

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);
}

TEST_F(TestRegionNoArgs,BasicRegionInteractions2)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::None
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
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

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);
}

TEST_F(TestRegionNoArgs,BasicRegionInteractions3)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::None
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
//    region.autoFinalize(false);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
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

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);

//    STTCL_TEST_LOG_END();
}

TEST_F(TestRegionNoArgs,BasicRegionInteractions4)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::None
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
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

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Interactions1)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
//    region.enableLogging(true);
//    innerState.enableLogging(true);

    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Interactions2)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Interactions3)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(false);

    STTCL_TEST_LOG_END();
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Interactions4)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState);
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState;

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(1);
    EXPECT_CALL(region,startingRegionThread())
        .Times(1);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(2);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(1);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(1);

    EXPECT_CALL(innerState,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
        .Times(1);
    EXPECT_CALL(innerState,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState,exitImpl(&region))
        .Times(1);

    // Run the state machine
    //----------------------------------------------------------------------------
    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Resume1)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;

    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState,"region");
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState1("innerState1");
    ::testing::NiceMock
        < TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType>
        > innerState2("innerState1");

    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState("outerState");

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState1);
    stateMachine.initialState(&compositeState);
    innerState1.setDirectTransitState(&innerState2);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(ConcurrentCompositeStateMockType, handleEvent1, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(region,startingRegionThread())
        .Times(2);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(3);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(2);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
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

    EXPECT_CALL(innerState1,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&region))
        .Times(1);
// Direct transition prevents initializing sub state machines
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(_))
//        .Times(1);
    EXPECT_CALL(innerState1,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&region))
        .Times(1);

    EXPECT_CALL(innerState2,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState2,startDoImpl(&region))
        .Times(1);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(false))
//        .Times(1);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(true))
//        .Times(1);
    EXPECT_CALL(innerState2,endDoImpl(&region))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&region))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------
//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.triggerEvent1();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.triggerEvent2();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));
    stateMachine.finalize(true);

//    STTCL_TEST_LOG_END();
}

TEST_F(TestRegionNoArgs,BasicRegion_ShallowHistory_Resume2)
{
    typedef TestConcurrentCompositeStateNoArgsMock
            < TestStateMachineNoEventArgsMock
            > ConcurrentCompositeStateMockType;
    typedef TestRegionNoArgsMock
            < ConcurrentCompositeStateMockType
            , sttcl::CompositeStateHistoryType::Shallow
            > RegionMockType;
    typedef TestRegionInnerStateNoArgsMock<ConcurrentCompositeStateMockType,RegionMockType> RegionInnerStateMockType;

    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");
    ::testing::NiceMock
        < ConcurrentCompositeStateMockType
        > compositeState(&stateMachine);
    ::testing::NiceMock
        < RegionMockType
        > region(&compositeState,"region");
    ::testing::NiceMock
        < RegionInnerStateMockType
        > innerState1("innerState1");
    ::testing::NiceMock
        < RegionInnerStateMockType
        > innerState2("innerState1");

    ::testing::NiceMock
        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
        > outerState("outerState");

    stateMachine.autoFinalize(false);
    compositeState.setRegion(0,&region);
    region.initialState(&innerState1);
    stateMachine.initialState(&compositeState);

    // Setup mock call expectations
    //----------------------------------------------------------------------------
    EXPECT_CALL(compositeState,handleEvent1(&stateMachine))
        .Times(1);
    EXPECT_CALL(compositeState,handleEvent2(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(ConcurrentCompositeStateMockType, handleEvent2, &compositeState, &outerState) );
    EXPECT_CALL(compositeState,endDoImpl(&stateMachine))
        .Times(2);
    EXPECT_CALL(compositeState,exitImpl(&stateMachine))
        .Times(2);

    // Check region calls
    EXPECT_CALL(region,enterRegionImpl(&compositeState))
        .Times(2);
    EXPECT_CALL(region,startingRegionThread())
        .Times(2);
    EXPECT_CALL(region,initializeImpl(_))
        .Times(3);
    EXPECT_CALL(region,finalizeImpl(_))
        .Times(2);
    EXPECT_CALL(region,endingRegionThread())
        .Times(2);
    EXPECT_CALL(region,exitRegionImpl(&compositeState))
        .Times(2);

    EXPECT_CALL(outerState,entryImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,handleEvent3(&stateMachine))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent3, &outerState, &compositeState) );
    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
        .Times(1);
    EXPECT_CALL(outerState,exitImpl(&stateMachine))
        .Times(1);

    EXPECT_CALL(innerState1,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState1,startDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState1,initSubStateMachinesImpl(true))
        .Times(1);
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(true))
//        .Times(1);
    EXPECT_CALL(innerState1,handleEvent1(&compositeState,&region))
        .Times(1)
        .WillOnce( TRIGGER_STATE_CHANGE2(RegionInnerStateMockType, handleEvent1, &innerState1, &innerState2) );
    EXPECT_CALL(innerState1,endDoImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState1,exitImpl(&region))
        .Times(1);

    EXPECT_CALL(innerState2,entryImpl(&region))
        .Times(1);
    EXPECT_CALL(innerState2,startDoImpl(&region))
        .Times(1);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(true))
//        .Times(1);
    EXPECT_CALL(innerState2,endDoImpl(&region))
        .Times(2);
    EXPECT_CALL(innerState2,exitImpl(&region))
        .Times(2);

    // Run the state machine
    //----------------------------------------------------------------------------

//    STTCL_TEST_LOG_ALL();

    stateMachine.initialize(true);
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));

    stateMachine.triggerEvent1();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));

    stateMachine.triggerEvent2();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));

    stateMachine.triggerEvent3();
    // Give the region thread(s) a chance to run
    sttcl::internal::SttclThread<>::sleep(sttcl::TimeDuration<>(0,0,0,100));

    stateMachine.finalize(true);

//    STTCL_TEST_LOG_END();
}

//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Interactions1)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState;
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,startDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
//        .Times(1);
//    EXPECT_CALL(innerState,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,exitImpl(&region))
//        .Times(1);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
////    region.enableLogging(true);
////    innerState.enableLogging(true);
//
//    stateMachine.initialize();
//    stateMachine.finalize(false);
//}
//
//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Interactions2)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState;
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,startDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
//        .Times(1);
//    EXPECT_CALL(innerState,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,exitImpl(&region))
//        .Times(1);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
//    stateMachine.initialize();
//    stateMachine.finalize(true);
//}
//
//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Interactions3)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState;
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,startDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,initSubStateMachinesImpl(false))
//        .Times(1);
////    EXPECT_CALL(innerState,initSubStateMachinesImpl(true))
////        .Times(1);
//    EXPECT_CALL(innerState,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,exitImpl(&region))
//        .Times(1);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
//    stateMachine.initialize(true);
//    stateMachine.finalize(false);
//}
//
//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Interactions4)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState;
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,startDoImpl(&region))
//        .Times(1);
////    EXPECT_CALL(innerState,initSubStateMachinesImpl(_))
////        .Times(1);
//    EXPECT_CALL(innerState,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState,exitImpl(&region))
//        .Times(1);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
//    stateMachine.initialize(true);
//    stateMachine.finalize(true);
//}
//
//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Resume1)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState1;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState2;
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
//        > outerState;
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine;
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState1);
//    innerState1.setDirectTransitState(&innerState2);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,handleEvent1(&stateMachine))
//        .Times(1)
//        .WillOnce( TRIGGER_STATE_CHANGE(RegionMockType, handleEvent1, &region, &outerState) );
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(2);
//
//    EXPECT_CALL(outerState,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
//        .Times(1)
//        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent1, &outerState, &region) );
//    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState1,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState1,startDoImpl(&region))
//        .Times(1);
//// Direct transition prevents initializing sub state machines
////    EXPECT_CALL(innerState1,initSubStateMachinesImpl(_))
////        .Times(1);
//    EXPECT_CALL(innerState1,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState1,exitImpl(&region))
//        .Times(1);
//
//    EXPECT_CALL(innerState2,entryImpl(&region))
//        .Times(2);
//    EXPECT_CALL(innerState2,startDoImpl(&region))
//        .Times(2);
//    EXPECT_CALL(innerState2,initSubStateMachinesImpl(_))
//        .Times(1);
//    EXPECT_CALL(innerState2,endDoImpl(&region))
//        .Times(2);
//    EXPECT_CALL(innerState2,exitImpl(&region))
//        .Times(2);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
//    stateMachine.initialize(true);
//    stateMachine.triggerEvent1();
//    stateMachine.triggerEvent2();
//    stateMachine.finalize(true);
//}
//
//TEST_F(TestRegionNoArgs,BasicCompositeState_DeepHistory_Resume2)
//{
//    typedef TestRegionNoArgsMock
//            < TestStateMachineNoEventArgsMock
//            , sttcl::CompositeStateHistoryType::Deep
//            > RegionMockType;
//    ::testing::NiceMock
//        < RegionMockType
//        > region("region");
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState1("innerState1");
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<RegionMockType>
//        > innerState2("innerState2");
//    ::testing::NiceMock
//        < TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>
//        > outerState("outerState");
//    ::testing::NiceMock<TestStateMachineNoEventArgsMock> stateMachine("stateMachine");
//
//    stateMachine.autoFinalize(false);
//    region.initialState(&innerState1);
//    stateMachine.initialState(&region);
//
//    // Setup mock call expectations
//    //----------------------------------------------------------------------------
//    EXPECT_CALL(region,entryImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,startDoImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,handleEvent1(&stateMachine))
//        .Times(1)
//        .WillOnce( TRIGGER_STATE_CHANGE(RegionMockType, handleEvent1, &region, &outerState) );
//    EXPECT_CALL(region,endDoImpl(&stateMachine))
//        .Times(2);
//    EXPECT_CALL(region,exitImpl(&stateMachine))
//        .Times(2);
//
//    EXPECT_CALL(outerState,entryImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,startDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,handleEvent2(&stateMachine))
//        .Times(1)
//        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<TestStateMachineNoEventArgsMock>, handleEvent2, &outerState, &region) );
//    EXPECT_CALL(outerState,endDoImpl(&stateMachine))
//        .Times(1);
//    EXPECT_CALL(outerState,exitImpl(&stateMachine))
//        .Times(1);
//
//    EXPECT_CALL(innerState1,entryImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState1,startDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState1,initSubStateMachinesImpl(false))
//        .Times(1);
//    EXPECT_CALL(innerState1,handleEvent1(&region))
//        .Times(1)
//        .WillOnce( TRIGGER_STATE_CHANGE(TestSimpleStateNoArgsMock<RegionMockType>, handleEvent1, &innerState1, &innerState2) );
//    EXPECT_CALL(innerState1,endDoImpl(&region))
//        .Times(1);
//    EXPECT_CALL(innerState1,exitImpl(&region))
//        .Times(1);
//
//    EXPECT_CALL(innerState2,entryImpl(&region))
//        .Times(2);
//    EXPECT_CALL(innerState2,startDoImpl(&region))
//        .Times(2);
////    EXPECT_CALL(innerState2,initSubStateMachinesImpl(false))
////        .Times(2);
//    EXPECT_CALL(innerState2,endDoImpl(&region))
//        .Times(2);
//    EXPECT_CALL(innerState2,exitImpl(&region))
//        .Times(2);
//
//    // Run the state machine
//    //----------------------------------------------------------------------------
//
////    STTCL_TEST_LOG_ALL();
//
//    stateMachine.initialize(true);
//    stateMachine.triggerEvent1();
//    stateMachine.triggerEvent2();
//    stateMachine.finalize(true);
//
////    STTCL_TEST_LOG_END();
//}
