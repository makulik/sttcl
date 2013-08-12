/*
 * Demo3CompositeState.h
 *
 *  Created on: Jul 3, 2013
 *      Author: user
 */

#ifndef DEMO3COMPOSITESTATE_H_
#define DEMO3COMPOSITESTATE_H_

#include "TestCompositeStateMocks.h"
#include "IDemo3EventHandler.h"

namespace Demo3
{

template
    < typename FinalClass
    , typename ContextClass
    , sttcl::CompositeStateHistoryType::Values HistoryType
    >
class Demo3CompositeState
: public TestCompositeStateMock
      < FinalClass
      , ContextClass
      , IDemo3EventHandler<ContextClass>
      , IDemo3EventHandler<FinalClass>
      , HistoryType
      >
{
public:
    typedef TestCompositeStateMock
            < FinalClass
            , ContextClass
            , IDemo3EventHandler<ContextClass>
            , IDemo3EventHandler<FinalClass>
            , HistoryType
            > MockBaseClass;

    Demo3CompositeState(const std::string& id)
    : MockBaseClass(id)
    {
        ON_CALL(*this, handleEvent1(_))
            .WillByDefault(Invoke(this, &Demo3CompositeState::propagateEvent1));
        ON_CALL(*this, handleEvent2(_))
            .WillByDefault(Invoke(this, &Demo3CompositeState::propagateEvent2));
        ON_CALL(*this, handleEvent3(_))
            .WillByDefault(Invoke(this, &Demo3CompositeState::propagateEvent3));
        ON_CALL(*this, handleEvent4(_))
            .WillByDefault(Invoke(this, &Demo3CompositeState::propagateEvent4));
        ON_CALL(*this, handleEvent5(_))
            .WillByDefault(Invoke(this, &Demo3CompositeState::propagateEvent5));
    }
    virtual ~Demo3CompositeState() {}

    MOCK_METHOD1_T(handleEvent1, void (ContextClass* context));
    MOCK_METHOD1_T(handleEvent2, void (ContextClass* context));
    MOCK_METHOD1_T(handleEvent3, void (ContextClass* context));
    MOCK_METHOD1_T(handleEvent4, void (ContextClass* context));
    MOCK_METHOD1_T(handleEvent5, void (ContextClass* context));

    virtual void propagateEvent1(ContextClass* context)
    {
        typename MockBaseClass::InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            currentState->handleEvent1(static_cast<FinalClass*>(this));
        }
    }

    virtual void propagateEvent2(ContextClass* context)
    {
        typename MockBaseClass::InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            currentState->handleEvent2(static_cast<FinalClass*>(this));
        }
    }

    virtual void propagateEvent3(ContextClass* context)
    {
        typename MockBaseClass::InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            currentState->handleEvent3(static_cast<FinalClass*>(this));
        }
    }

    virtual void propagateEvent4(ContextClass* context)
    {
        typename MockBaseClass::InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            currentState->handleEvent4(static_cast<FinalClass*>(this));
        }
    }

    virtual void propagateEvent5(ContextClass* context)
    {
        typename MockBaseClass::InnerStateBaseClass* currentState = MockBaseClass::getState();
        if(currentState)
        {
            currentState->handleEvent5(static_cast<FinalClass*>(this));
        }
    }
};

}
#endif /* DEMO3COMPOSITESTATE_H_ */
