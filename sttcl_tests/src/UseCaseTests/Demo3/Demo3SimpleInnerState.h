/*
 * Demo3SimpleInnerState.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef DEMO3SIMPLESTATE_H_
#define DEMO3SIMPLESTATE_H_

#include "TestStateMocks.h"
#include "IDemo3EventHandler.h"

namespace Demo3
{

template
< typename CompositeState
>
class Demo3SimpleInnerState
: public TestStateMock<Demo3SimpleInnerState<CompositeState>,CompositeState,IDemo3EventHandler<CompositeState> >
{
public:
    typedef TestStateMock<Demo3SimpleInnerState<CompositeState>,CompositeState,IDemo3EventHandler<CompositeState> > MockBaseClass;

    Demo3SimpleInnerState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    Demo3SimpleInnerState(const Demo3SimpleInnerState& rhs)
    : MockBaseClass(rhs)
    {}
    virtual ~Demo3SimpleInnerState() {}

    MOCK_METHOD1_T(handleEvent1, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent2, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent3, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent4, void (CompositeState* context));
    MOCK_METHOD1_T(handleEvent5, void (CompositeState* context));

};
}
#endif /* DEMO3SIMPLESTATE_H_ */
