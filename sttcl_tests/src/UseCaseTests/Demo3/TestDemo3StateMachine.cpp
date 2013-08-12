/*
 * TestDemo3StateMachine.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "DemoState3.h"
#include "Demo3StateMachine.h"

#include "SttclTestActions.h"
#include "Demo3ActionDefinitions.h"

using ::testing::DoAll;
using ::testing::ByRef;

class TestDemo3StateMachine: public ::testing::Test
{
public:

    typedef testing::NiceMock<Demo3::Demo3StateMachine> RootStateMachineType;

    TestDemo3StateMachine()
    : demo3StateMachine()
    , demoState1(demo3StateMachine.DemoState1())
    , demoState2(demo3StateMachine.DemoState2())
    , demoState3(demo3StateMachine.DemoState3())
    , demoState3a(demoState3.DemoState3a())
    , demoState3b(demoState3.DemoState3b())
    , demoState3c(demoState3.DemoState3c())
    {
    }

    ~TestDemo3StateMachine()
    {
    }

    virtual void SetUp()
    {
        // Setup the state diagram transitions
        //--------------------------------------------------------------------------------------------------
        // ** DemoState1 **
        ON_CALL(demoState1,handleEvent1(&demo3StateMachine))
           .WillByDefault (
               DoAll
               ( EventDefaultAction<RootInnerStateType>(&rootEventActionStates,false,&demoState2)
               , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState1,&rootEventActionStates)
               )
            );
        ON_CALL(demoState1,handleEvent2(&demo3StateMachine))
            .WillByDefault (
                DoAll
                ( GuardCompareX<RootInnerStateType,std::greater_equal<int> >(&rootEventActionStates,3,false,&demoState3)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState1,&rootEventActionStates)
                )
         );

        // ** DemoState2 **
        ON_CALL(demoState2,handleEvent2(&demo3StateMachine))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<RootInnerStateType>(&rootEventActionStates,true,(RootInnerStateType*)0)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState2,&rootEventActionStates)
                )
             );
        ON_CALL(demoState2,handleEvent1(&demo3StateMachine))
            .WillByDefault (
                DoAll
                ( GuardCompareY<RootInnerStateType,std::less<int> >(&rootEventActionStates,4,false,&demoState3)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState2,&rootEventActionStates)
                )
             );

        // ** DemoState3 **
        demoState3.initialState(&demoState3b);

        ON_CALL(demoState3,handleEvent3(&demo3StateMachine))
            .WillByDefault (
                DoAll
                ( Invoke(&demoState3, &Demo3::DemoState3::propagateEvent3)
                , EventDefaultAction<RootInnerStateType>(&rootEventActionStates,false,&demoState1)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState3,&rootEventActionStates)
                )
             );

        // ** DemoState3a **
        ON_CALL(demoState3a,handleEvent2(&demoState3))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3InnerStateType>(&demoState3EventActionStates,false,&demoState3c)
                , PerformStateChangeOrFinalize<DemoState3InnerStateType>(&demoState3a,&demoState3EventActionStates)
                )
             );
        ON_CALL(demoState3a,handleEvent5(&demoState3))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3InnerStateType>(&demoState3EventActionStates,false,&demoState3b)
                , PerformStateChangeOrFinalize<DemoState3InnerStateType>(&demoState3a,&demoState3EventActionStates)
                )
             );

        // ** DemoState3b **
        ON_CALL(demoState3b,handleEvent1(&demoState3))
            .WillByDefault (
                DoAll
                ( GuardCompareZ<DemoState3InnerStateType,std::equal_to<int> >(&demoState3EventActionStates,3,false,&demoState3c)
                , PerformStateChangeOrFinalize<DemoState3InnerStateType>(&demoState3b,&demoState3EventActionStates)
                )
             );

        // ** DemoState3c **
        ON_CALL(demoState3c,handleEvent4(&demoState3))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3InnerStateType>(&demoState3EventActionStates,true,(DemoState3InnerStateType*)0)
                , PerformStateChangeOrFinalize<DemoState3InnerStateType>(&demoState3c,&demoState3EventActionStates)
                )
             );

        demo3StateMachine.initialState(&demoState1);
        demoState3.initialState(&demoState3a);
    }

protected:
    void resetAllActionStates()
    {
        rootEventActionStates.reset();
        demoState3EventActionStates.reset();
    }

    RootStateMachineType demo3StateMachine;
    typedef RootStateMachineType::StateBaseClass RootInnerStateType;

    RootStateMachineType::SimpleInnerStateType& demoState1;
    RootStateMachineType::SimpleInnerStateType& demoState2;

    Demo3::DemoState3& demoState3;
    typedef Demo3::DemoState3::InnerStateBaseClass DemoState3InnerStateType;

    Demo3::DemoState3::SimpleInnerStateType& demoState3a;
    Demo3::DemoState3::SimpleInnerStateType& demoState3b;
    Demo3::DemoState3::SimpleInnerStateType& demoState3c;

    EventActionStates<RootInnerStateType> rootEventActionStates;
    EventActionStates<DemoState3InnerStateType> demoState3EventActionStates;
};

TEST_F(TestDemo3StateMachine,UseCaseScenario1)
{

    STTCL_TEST_LOG_ALL();

    demo3StateMachine.initialize();
    EXPECT_EQ(&demoState1,demo3StateMachine.getState());
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState2,demo3StateMachine.getState());
    rootEventActionStates.reset();
    demo3StateMachine.triggerEvent2();
    EXPECT_TRUE(demo3StateMachine.isFinalized());

    STTCL_TEST_LOG_END();
}

TEST_F(TestDemo3StateMachine,UseCaseScenario2)
{

    STTCL_TEST_LOG_ALL();

    resetAllActionStates();
    demo3StateMachine.initialize();
    EXPECT_EQ(&demoState1,demo3StateMachine.getState());

    // ** Step 1
    resetAllActionStates();
    demo3StateMachine.x(4); // Fulfill the guard condition
    demo3StateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3a,demoState3.getState());

    // ** Step 2
    resetAllActionStates();
    demo3StateMachine.triggerEvent5();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());

    // ** Step 3
    resetAllActionStates();
    demo3StateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());

    // ** Step 4
    resetAllActionStates();
    demo3StateMachine.triggerEvent3();
    EXPECT_EQ(&demoState1,demo3StateMachine.getState());
    EXPECT_EQ(NULL,demoState3.getState());

    // ** Step 5
    resetAllActionStates();
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState2,demo3StateMachine.getState());
    EXPECT_EQ(NULL,demoState3.getState());

    // ** Step 6
    resetAllActionStates();
    demo3StateMachine.y(3); // Fulfill the guard condition
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());

    //    rootEventActionStates.reset();
//    demo3StateMachine.triggerEvent2();
//    EXPECT_TRUE(demo3StateMachine.isFinalized());

    demo3StateMachine.finalize(true);

    STTCL_TEST_LOG_END();
}

TEST_F(TestDemo3StateMachine,UseCaseScenario3)
{

    STTCL_TEST_LOG_ALL();

    resetAllActionStates();
    demo3StateMachine.initialize();
    EXPECT_EQ(&demoState1,demo3StateMachine.getState());

    // ** Step 1
    resetAllActionStates();
    demo3StateMachine.x(4); // Fulfill the guard condition
    demo3StateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3a,demoState3.getState());

    // ** Step 2
    resetAllActionStates();
    demo3StateMachine.triggerEvent5();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());

    // ** Step 3
    resetAllActionStates();
    demo3StateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());

    // ** Step 4
    resetAllActionStates();
    demoState3.z(3); // Fulfill the guard condition
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3c,demoState3.getState());

    // ** Step 5
    resetAllActionStates();
    demo3StateMachine.triggerEvent4();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_TRUE(demoState3.isFinalized());

    // ** Step 6
    resetAllActionStates();
    demo3StateMachine.triggerEvent3();
    EXPECT_EQ(&demoState1,demo3StateMachine.getState());

    // ** Step 7
    resetAllActionStates();
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState2,demo3StateMachine.getState());

    // ** Step 4
    resetAllActionStates();
    demo3StateMachine.y(3); // Fulfill the guard condition
    demo3StateMachine.triggerEvent1();
    EXPECT_EQ(&demoState3,demo3StateMachine.getState());
    EXPECT_EQ(&demoState3a,demoState3.getState());

    demo3StateMachine.finalize(true);

    STTCL_TEST_LOG_END();
}
