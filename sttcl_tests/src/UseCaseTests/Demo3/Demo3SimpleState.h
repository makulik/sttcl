/*
 * Demo3SimpleState.h
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

class Demo3StateMachine;

class Demo3SimpleState
: public TestStateMock<Demo3SimpleState,Demo3StateMachine,IDemo3EventHandler<Demo3StateMachine> >
{
public:
    typedef TestStateMock<Demo3SimpleState,Demo3StateMachine,IDemo3EventHandler<Demo3StateMachine> > MockBaseClass;

    Demo3SimpleState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    virtual ~Demo3SimpleState() {}

    MOCK_METHOD1(handleEvent1, void (Demo3StateMachine* context));
    MOCK_METHOD1(handleEvent2, void (Demo3StateMachine* context));
    MOCK_METHOD1(handleEvent3, void (Demo3StateMachine* context));
    MOCK_METHOD1(handleEvent4, void (Demo3StateMachine* context));
    MOCK_METHOD1(handleEvent5, void (Demo3StateMachine* context));

};
}
#endif /* DEMO3SIMPLESTATE_H_ */
