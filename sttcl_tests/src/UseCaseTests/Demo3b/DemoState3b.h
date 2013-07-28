/*
 * DemoState3b.h
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#ifndef DEMOSTATE3B_H_
#define DEMOSTATE3B_H_
#include <memory>

#include "CommonSTLTranslators.h"
#include "Demo3bCompositeState.h"
#include "Demo3bSimpleInnerState.h"
#include "DemoState3.h"

namespace Demo3b
{
class DemoState3b;

class DemoState3b
: public Demo3bCompositeState<DemoState3b, Demo3b::DemoState3, sttcl::CompositeStateHistoryType::Shallow>
{
public:
    typedef Demo3bCompositeState<DemoState3b, Demo3b::DemoState3, sttcl::CompositeStateHistoryType::Shallow> MockBase;
    typedef Demo3bSimpleInnerState<DemoState3b> SimpleInnerStateType;

    DemoState3b(const std::string& id = "DemoState3b");
    virtual ~DemoState3b();

    SimpleInnerStateType& DemoState3b_1();
    SimpleInnerStateType& DemoState3b_2();
    SimpleInnerStateType& DemoState3b_3();

private:

    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3b_1;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3b_2;
    mutable sttcl_tests::AutoPtr<SimpleInnerStateType>::Type demoState3b_3;
};
} /* namespace Demo3b */
#endif /* DEMOSTATE3B_H_ */
