/*
 * Demo3aStateMachine.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef DEMO3ASTATEMACHINE_H_
#define DEMO3ASTATEMACHINE_H_
#include <memory>

#include "CommonSTLTranslators.h"

#include "Mocks/TestStateMachineMocks.h"
#include "IDemo3aEventHandler.h"
#include "Demo3aSimpleInnerState.h"

namespace Demo3a
{
    class Demo3aStateMachine;
    class DemoState3;

    class Demo3aStateMachine
    : public TestStateMachineMock<Demo3aStateMachine,IDemo3aEventHandler<Demo3aStateMachine> >
    {
    public:
        typedef TestStateMachineMock<Demo3aStateMachine,IDemo3aEventHandler<Demo3aStateMachine> > MockBaseClass;
        typedef Demo3aSimpleInnerState<Demo3aStateMachine> SimpleInnerStateType;
        typedef MockBaseClass::StateBaseClass StateBaseClass;

        Demo3aStateMachine();
        ~Demo3aStateMachine();

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
        Demo3a::DemoState3& DemoState3();

    private:
        int x_;
        int y_;

        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState1_;
        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState2_;
        mutable sttcl_tests::AutoPtr<Demo3a::DemoState3>::Type demoState3_;
    };
}

#endif /* DEMO3ASTATEMACHINE_H_ */
