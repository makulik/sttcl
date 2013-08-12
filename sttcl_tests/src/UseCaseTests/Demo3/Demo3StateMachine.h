/*
 * Demo3StateMachine.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef DEMO3ASTATEMACHINE_H_
#define DEMO3ASTATEMACHINE_H_
#include <memory>

#include "CommonSTLTranslators.h"

#include "Mocks/TestStateMachineMocks.h"
#include "IDemo3EventHandler.h"
#include "Demo3SimpleInnerState.h"

namespace Demo3
{
    class Demo3StateMachine;
    class DemoState3;

    class Demo3StateMachine
    : public TestStateMachineMock<Demo3StateMachine,IDemo3EventHandler<Demo3StateMachine> >
    {
    public:
        typedef TestStateMachineMock<Demo3StateMachine,IDemo3EventHandler<Demo3StateMachine> > MockBaseClass;
        typedef Demo3SimpleInnerState<Demo3StateMachine> SimpleInnerStateType;
        typedef MockBaseClass::StateBaseClass StateBaseClass;

        Demo3StateMachine();
        ~Demo3StateMachine();

        void triggerEvent1();
        void triggerEvent2();
        void triggerEvent3();
        void triggerEvent4();
        void triggerEvent5();

        int x() const { return x_; }
        void x(int value) { x_ = value; }
        int y() const { return y_; }
        void y(int value) { y_ = value; }

        SimpleInnerStateType& DemoState1();
        SimpleInnerStateType& DemoState2();
        Demo3::DemoState3& DemoState3();

    private:
        int x_;
        int y_;

        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState1_;
        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState2_;
        mutable sttcl_tests::AutoPtr<Demo3::DemoState3>::Type demoState3_;
    };
}

#endif /* DEMO3ASTATEMACHINE_H_ */
