/*
 * Demo3aSimpleInnerState.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef DEMO3ASIMPLESTATE_H_
#define DEMO3ASIMPLESTATE_H_

#include "TestStateMocks.h"
#include "IDemo3aEventHandler.h"

namespace Demo3a
{

template
< typename CompositeState
>
class Demo3aSimpleInnerState
: public TestStateMock<Demo3aSimpleInnerState<CompositeState>,CompositeState,IDemo3aEventHandler<CompositeState> >
{
public:
    typedef TestStateMock<Demo3aSimpleInnerState<CompositeState>,CompositeState,IDemo3aEventHandler<CompositeState> > MockBaseClass;

    Demo3aSimpleInnerState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    Demo3aSimpleInnerState(const Demo3aSimpleInnerState& rhs)
    : MockBaseClass(rhs)
    {}
    virtual ~Demo3aSimpleInnerState() {}

    MOCK_METHOD1_T(handleEvent1, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent2, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent3, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent4, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent5, void (CompositeState* context));

};
}
#endif /* DEMO3ASIMPLESTATE_H_ */
