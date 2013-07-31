/*
 * DemoState3b.h
 *
 *  Created on: Jul 5, 2013
 *      Author: user
 */

#ifndef DEMO3A_DEMOSTATE3B_H_
#define DEMO3A_DEMOSTATE3B_H_
#include <memory>

#include "CommonSTLTranslators.h"
#include "Demo3aCompositeState.h"
#include "Demo3aSimpleInnerState.h"
#include "DemoState3.h"

namespace Demo3a
{
class DemoState3b;

class DemoState3b
: public Demo3aCompositeState<DemoState3b, Demo3a::DemoState3, sttcl::CompositeStateHistoryType::Shallow>
{
public:
    typedef Demo3aCompositeState<DemoState3b, Demo3a::DemoState3, sttcl::CompositeStateHistoryType::Shallow> MockBase;
    typedef Demo3aSimpleInnerState<DemoState3b> SimpleInnerStateType;

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
} /* namespace Demo3a */
#endif /* DEMO3A_DEMOSTATE3B_H_ */
