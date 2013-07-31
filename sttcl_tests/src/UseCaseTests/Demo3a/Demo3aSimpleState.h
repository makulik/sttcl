/*
 * Demo3aSimpleState.h
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

class Demo3aStateMachine;

class Demo3aSimpleState
: public TestStateMock<Demo3aSimpleState,Demo3aStateMachine,IDemo3aEventHandler<Demo3aStateMachine> >
{
public:
    typedef TestStateMock<Demo3aSimpleState,Demo3aStateMachine,IDemo3aEventHandler<Demo3aStateMachine> > MockBaseClass;

    Demo3aSimpleState(const std::string& id = "<anonymous>")
    : MockBaseClass(id)
    {}
    virtual ~Demo3aSimpleState() {}

    MOCK_METHOD1(handleEvent1, void (Demo3aStateMachine* context));
    MOCK_METHOD1(handleEvent2, void (Demo3aStateMachine* context));
    MOCK_METHOD1(handleEvent3, void (Demo3aStateMachine* context));
    MOCK_METHOD1(handleEvent4, void (Demo3aStateMachine* context));
    MOCK_METHOD1(handleEvent5, void (Demo3aStateMachine* context));

};
}
#endif /* DEMO3ASIMPLESTATE_H_ */
