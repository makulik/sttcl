/*
 * DemoState3.h
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#ifndef DEMO3_DEMOSTATE3_H_
#define DEMO3_DEMOSTATE3_H_

//#include "CommonSTLTranslators.h"
#include <memory>

#include "Demo3CompositeState.h"
#include "Demo3SimpleInnerState.h"
#include "Demo3StateMachine.h"

namespace Demo3
{

class Demo3StateMachine;
class DemoState3;

class DemoState3
: public Demo3CompositeState<DemoState3, Demo3::Demo3StateMachine, sttcl::CompositeStateHistoryType::Shallow>
{
public:
    typedef Demo3CompositeState<DemoState3, Demo3::Demo3StateMachine, sttcl::CompositeStateHistoryType::Shallow> MockBaseClass;
    typedef Demo3SimpleInnerState<DemoState3> SimpleInnerStateType;

    DemoState3(const std::string& id = "DemoState3");
    virtual ~DemoState3();


    int z() const { return z_; }
    void z(int value) { z_ = value; }

    SimpleInnerStateType& DemoState3a();
    SimpleInnerStateType& DemoState3b();
    SimpleInnerStateType& DemoState3c();

private:
    int z_;

    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3a_;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3b_;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3c_;
};
} /* namespace Demo3 */
#endif /* DEMO3_DEMOSTATE3_H_ */
