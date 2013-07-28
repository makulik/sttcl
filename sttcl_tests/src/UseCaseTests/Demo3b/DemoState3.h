/*
 * DemoState3.h
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#ifndef DEMOSTATE3_H_
#define DEMOSTATE3_H_

//#include "CommonSTLTranslators.h"
#include <memory>

#include "Demo3bCompositeState.h"
#include "Demo3bSimpleInnerState.h"
#include "Demo3bStateMachine.h"

namespace Demo3b
{

class Demo3bStateMachine;
class DemoState3;
class DemoState3b;

class DemoState3
: public Demo3bCompositeState<DemoState3, Demo3b::Demo3bStateMachine, sttcl::CompositeStateHistoryType::Deep>
{
public:
    typedef Demo3bCompositeState<DemoState3, Demo3b::Demo3bStateMachine, sttcl::CompositeStateHistoryType::Deep> MockBaseClass;
    typedef Demo3bSimpleInnerState<DemoState3> SimpleInnerStateType;

    DemoState3(const std::string& id = "DemoState3");
    virtual ~DemoState3();


    int z() const { return z_; }
    void z(int value) { z_ = value; }

    SimpleInnerStateType& DemoState3a();
    Demo3b::DemoState3b& DemoState3b();
    SimpleInnerStateType& DemoState3c();

private:
    int z_;

    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3a_;
    mutable sttcl_tests::AutoPtr<Demo3b::DemoState3b>::Type demoState3b_;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3c_;
};
} /* namespace Demo3b */
#endif /* DEMOSTATE3_H_ */
