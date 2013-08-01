/*
 * Demo3bStateMachine.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef DEMO3BSTATEMACHINE_H_
#define DEMO3BSTATEMACHINE_H_
#include <memory>

#include "CommonSTLTranslators.h"

#include "Mocks/TestStateMachineMocks.h"
#include "IDemo3bEventHandler.h"
#include "Demo3bSimpleInnerState.h"

namespace Demo3b
{
    class Demo3bStateMachine;
    class DemoState3;

    class Demo3bStateMachine
    : public TestStateMachineMock<Demo3bStateMachine,IDemo3bEventHandler<Demo3bStateMachine> >
    {
    public:
        typedef TestStateMachineMock<Demo3bStateMachine,IDemo3bEventHandler<Demo3bStateMachine> > MockBaseClass;
        typedef Demo3bSimpleInnerState<Demo3bStateMachine> SimpleInnerStateType;
        typedef MockBaseClass::StateBaseClass StateBaseClass;

        Demo3bStateMachine();
        ~Demo3bStateMachine();

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
        Demo3b::DemoState3& DemoState3();

    private:
        int x_;
        int y_;

        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState1_;
        mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState2_;
        mutable sttcl_tests::AutoPtr<Demo3b::DemoState3>::Type demoState3_;
    };
}

#endif /* DEMO3BSTATEMACHINE_H_ */
