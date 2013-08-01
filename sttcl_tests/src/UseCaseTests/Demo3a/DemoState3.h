/*
 * DemoState3.h
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#ifndef DEMO3A_DEMOSTATE3_H_
#define DEMO3A_DEMOSTATE3_H_

//#include "CommonSTLTranslators.h"
#include <memory>

#include "Demo3aCompositeState.h"
#include "Demo3aSimpleInnerState.h"
#include "Demo3aStateMachine.h"

namespace Demo3a
{

class Demo3aStateMachine;
class DemoState3;
class DemoState3b;

class DemoState3
: public Demo3aCompositeState<DemoState3, Demo3a::Demo3aStateMachine, sttcl::CompositeStateHistoryType::Shallow>
{
public:
    typedef Demo3aCompositeState<DemoState3, Demo3a::Demo3aStateMachine, sttcl::CompositeStateHistoryType::Shallow> MockBaseClass;
    typedef Demo3aSimpleInnerState<DemoState3> SimpleInnerStateType;

    DemoState3(const std::string& id = "DemoState3");
    virtual ~DemoState3();


    int z() const { return z_; }
    void z(int value) { z_ = value; }

    SimpleInnerStateType& DemoState3a();
    Demo3a::DemoState3b& DemoState3b();
    SimpleInnerStateType& DemoState3c();

private:
    int z_;

    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3a_;
    mutable sttcl_tests::AutoPtr<Demo3a::DemoState3b>::Type demoState3b_;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3c_;
};
} /* namespace Demo3a */
#endif /* DEMO3A_DEMOSTATE3_H_ */
