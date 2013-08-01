/*
 * Demo3bSimpleState.h
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

class Demo3bStateMachine;

class Demo3bSimpleState
: public TestStateMock<Demo3bSimpleState,Demo3bStateMachine,IDemo3bEventHandler<Demo3bStateMachine> >
{
public:
    typedef TestStateMock<Demo3bSimpleState,Demo3bStateMachine,IDemo3bEventHandler<Demo3bStateMachine> > MockBaseClass;

    Demo3bSimpleState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    virtual ~Demo3bSimpleState() {}

    MOCK_METHOD1(handleEvent1, void (Demo3bStateMachine* context));
    MOCK_METHOD1(handleEvent2, void (Demo3bStateMachine* context));
    MOCK_METHOD1(handleEvent3, void (Demo3bStateMachine* context));
    MOCK_METHOD1(handleEvent4, void (Demo3bStateMachine* context));
    MOCK_METHOD1(handleEvent5, void (Demo3bStateMachine* context));

};
}
#endif /* DEMO3BSIMPLESTATE_H_ */
