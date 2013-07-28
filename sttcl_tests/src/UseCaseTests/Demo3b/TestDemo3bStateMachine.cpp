/*
 * TestDemo3bStateMachine.cpp
 *
 *  Created on: May 21, 2013
 *      Author: user
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "DemoState3b.h"
#include "DemoState3.h"
#include "Demo3bStateMachine.h"

#include "SttclTestActions.h"
#include "Demo3bActionDefinitions.h"

using ::testing::DoAll;
using ::testing::ByRef;

class TestDemo3bStateMachine: public ::testing::Test
{
public:

    typedef testing::NiceMock<Demo3b::Demo3bStateMachine> RootStateMachineType;

    TestDemo3bStateMachine()
    : demo3bStateMachine()
    , demoState1(demo3bStateMachine.DemoState1())
    , demoState2(demo3bStateMachine.DemoState2())
    , demoState3(demo3bStateMachine.DemoState3())
    , demoState3a(demoState3.DemoState3a())
    , demoState3b(demoState3.DemoState3b())
    , demoState3c(demoState3.DemoState3c())
    , demoState3b_1(demoState3b.DemoState3b_1())
    , demoState3b_2(demoState3b.DemoState3b_2())
    , demoState3b_3(demoState3b.DemoState3b_3())
    {
    }

    ~TestDemo3bStateMachine()
    {
    }

    virtual void SetUp()
    {
        // Setup the state diagram transitions
        //--------------------------------------------------------------------------------------------------
        // ** DemoState1 **
        ON_CALL(demoState1,handleEvent1(&demo3bStateMachine))
           .WillByDefault (
               DoAll
               ( EventDefaultAction<RootInnerStateType>(&rootEventActionStates,false,&demoState2)
               , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState1,&rootEventActionStates)
               )
            );
        ON_CALL(demoState1,handleEvent2(&demo3bStateMachine))
            .WillByDefault (
                DoAll
                ( GuardCompareX<RootInnerStateType,std::greater_equal<int> >(&rootEventActionStates,3,false,&demoState3)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState1,&rootEventActionStates)
                )
         );

        // ** DemoState2 **
        ON_CALL(demoState2,handleEvent2(&demo3bStateMachine))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<RootInnerStateType>(&rootEventActionStates,true,(RootInnerStateType*)0)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState2,&rootEventActionStates)
                )
             );
        ON_CALL(demoState2,handleEvent1(&demo3bStateMachine))
            .WillByDefault (
                DoAll
                ( GuardCompareY<RootInnerStateType,std::less<int> >(&rootEventActionStates,4,false,&demoState3)
                , PerformStateChangeOrFinalize<RootInnerStateType>(&demoState2,&rootEventActionStates)
                )
             );

        // ** DemoState3 **
        demoState3.initialState(&demoState3b);

        ON_CALL(demoState3,handleEvent3(&demo3bStateMachine))
            .WillByDefault (
                DoAll
                ( Invoke(&demoState3, &Demo3b::DemoState3::propagateEvent3)
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

        // ** DemoState3b_1 **
        ON_CALL(demoState3b_1,handleEvent2(&demoState3b))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3bInnerStateType>(&demoState3bEventActionStates,false,&demoState3b_2)
                , PerformStateChangeOrFinalize<DemoState3bInnerStateType>(&demoState3b_1,&demoState3bEventActionStates)
                )
             );

        // ** DemoState3b_2 **
        ON_CALL(demoState3b_2,handleEvent3(&demoState3b))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3bInnerStateType>(&demoState3bEventActionStates,false,&demoState3b_3)
                , PerformStateChangeOrFinalize<DemoState3bInnerStateType>(&demoState3b_2,&demoState3bEventActionStates)
                )
             );

        // ** DemoState3b_3 **
        ON_CALL(demoState3b_3,handleEvent1(&demoState3b))
            .WillByDefault (
                DoAll
                ( EventDefaultAction<DemoState3bInnerStateType>(&demoState3bEventActionStates,false,&demoState3b_1)
                , PerformStateChangeOrFinalize<DemoState3bInnerStateType>(&demoState3b_3,&demoState3bEventActionStates)
                )
             );
        //--------------------------------------------------------------------------------------------------

        demo3bStateMachine.initialState(&demoState1);
        demoState3.initialState(&demoState3a);
    }

protected:
    void resetAllActionStates()
    {
        rootEventActionStates.reset();
        demoState3EventActionStates.reset();
        demoState3bEventActionStates.reset();
    }

    RootStateMachineType demo3bStateMachine;
    typedef RootStateMachineType::StateBaseClass RootInnerStateType;

    RootStateMachineType::SimpleInnerStateType& demoState1;
    RootStateMachineType::SimpleInnerStateType& demoState2;

    Demo3b::DemoState3& demoState3;
    typedef Demo3b::DemoState3::InnerStateBaseClass DemoState3InnerStateType;

    Demo3b::DemoState3::SimpleInnerStateType& demoState3a;
    Demo3b::DemoState3b& demoState3b;
    typedef Demo3b::DemoState3b::InnerStateBaseClass DemoState3bInnerStateType;
    Demo3b::DemoState3::SimpleInnerStateType& demoState3c;

    Demo3b::DemoState3b::SimpleInnerStateType& demoState3b_1;
    Demo3b::DemoState3b::SimpleInnerStateType& demoState3b_2;
    Demo3b::DemoState3b::SimpleInnerStateType& demoState3b_3;

    EventActionStates<RootInnerStateType> rootEventActionStates;
    EventActionStates<DemoState3InnerStateType> demoState3EventActionStates;
    EventActionStates<DemoState3bInnerStateType> demoState3bEventActionStates;
};

TEST_F(TestDemo3bStateMachine,UseCaseScenario1)
{

    STTCL_TEST_LOG_ALL();

    demo3bStateMachine.initialize();
    EXPECT_EQ(&demoState1,demo3bStateMachine.getState());
    demo3bStateMachine.triggerEvent1();
    EXPECT_EQ(&demoState2,demo3bStateMachine.getState());
    rootEventActionStates.reset();
    demo3bStateMachine.triggerEvent2();
    EXPECT_TRUE(demo3bStateMachine.isFinalized());

    STTCL_TEST_LOG_END();
}

TEST_F(TestDemo3bStateMachine,UseCaseScenario2)
{

    STTCL_TEST_LOG_ALL();

    resetAllActionStates();
    demo3bStateMachine.initialize();
    EXPECT_EQ(&demoState1,demo3bStateMachine.getState());

    // ** Step 1
    resetAllActionStates();
    demo3bStateMachine.x(4); // Fulfill the guard condition
    demo3bStateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3bStateMachine.getState());
    EXPECT_EQ(&demoState3a,demoState3.getState());

    // ** Step 2
    resetAllActionStates();
    demo3bStateMachine.triggerEvent5();
    EXPECT_EQ(&demoState3,demo3bStateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());
    EXPECT_EQ(&demoState3b_1,demoState3b.getState());

    // ** Step 3
    resetAllActionStates();
    demo3bStateMachine.triggerEvent2();
    EXPECT_EQ(&demoState3,demo3bStateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());
    EXPECT_EQ(&demoState3b_2,demoState3b.getState());

    // ** Step 4
    resetAllActionStates();
    demo3bStateMachine.triggerEvent3();
    EXPECT_EQ(&demoState1,demo3bStateMachine.getState());
    EXPECT_EQ(NULL,demoState3.getState());
    EXPECT_EQ(NULL,demoState3b.getState());

    // ** Step 5
    resetAllActionStates();
    demo3bStateMachine.triggerEvent1();
    EXPECT_EQ(&demoState2,demo3bStateMachine.getState());
    EXPECT_EQ(NULL,demoState3.getState());
    EXPECT_EQ(NULL,demoState3b.getState());

    // ** Step 6
    resetAllActionStates();
    demo3bStateMachine.y(3); // Fulfill the guard condition
    demo3bStateMachine.triggerEvent1();
    EXPECT_EQ(&demoState3,demo3bStateMachine.getState());
    EXPECT_EQ(&demoState3b,demoState3.getState());
    EXPECT_EQ(&demoState3b_3,demoState3b.getState());

    //    rootEventActionStates.reset();
//    demo3bStateMachine.triggerEvent2();
//    EXPECT_TRUE(demo3bStateMachine.isFinalized());

    demo3bStateMachine.finalize(true);

    STTCL_TEST_LOG_END();
}
