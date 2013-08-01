/*
 * Demo3bSimpleInnerState.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef DEMO3BSIMPLESTATE_H_
#define DEMO3BSIMPLESTATE_H_

#include "TestStateMocks.h"
#include "IDemo3bEventHandler.h"

namespace Demo3b
{

template
< typename CompositeState
>
class Demo3bSimpleInnerState
: public TestStateMock<Demo3bSimpleInnerState<CompositeState>,CompositeState,IDemo3bEventHandler<CompositeState> >
{
public:
    typedef TestStateMock<Demo3bSimpleInnerState<CompositeState>,CompositeState,IDemo3bEventHandler<CompositeState> > MockBaseClass;

    Demo3bSimpleInnerState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    Demo3bSimpleInnerState(const Demo3bSimpleInnerState& rhs)
    : MockBaseClass(rhs)
    {}
    virtual ~Demo3bSimpleInnerState() {}

    MOCK_METHOD1_T(handleEvent1, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent2, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent3, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent4, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent5, void (CompositeState* context));

};
}
#endif /* DEMO3BSIMPLESTATE_H_ */
