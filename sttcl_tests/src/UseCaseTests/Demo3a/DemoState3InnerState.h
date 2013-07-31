/*
 * DemoState3SimpleInnerState.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef DEMO3A_DEMOSTATE3SIMPLEINNSERSTATE_H_
#define DEMO3A_DEMOSTATE3SIMPLEINNSERSTATE_H_

#include "TestStateMocks.h"
#include "IDemo3aEventHandler.h"

namespace Demo3a
{
class DemoState3;

class DemoState3SimpleInnerState
: public TestStateMock<DemoState3SimpleInnerState,DemoState3,IDemo3aEventHandler<DemoState3> >
{
public:
    typedef TestStateMock<DemoState3SimpleInnerState,DemoState3,IDemo3aEventHandler<DemoState3> > MockBaseClass;

    DemoState3SimpleInnerState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    virtual ~DemoState3SimpleInnerState() {}

    MOCK_METHOD1(handleEvent1, void (DemoState3* context));
    MOCK_METHOD1(handleEvent2, void (DemoState3* context));
    MOCK_METHOD1(handleEvent3, void (DemoState3* context));
    MOCK_METHOD1(handleEvent4, void (DemoState3* context));
    MOCK_METHOD1(handleEvent5, void (DemoState3* context));
};

} /* namespace Demo3a */
#endif /* DEMO3A_DEMOSTATE3SIMPLEINNSERSTATE_H_ */

