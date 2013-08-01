/*
 * Demo3bActionDefinitions.h
 *
 *  Created on: Jul 21, 2013
 *      Author: user
 */

#ifndef DEMO3BACTIONDEFINITIONS_H_
#define DEMO3BACTIONDEFINITIONS_H_

#include <gmock/gmock.h>

template<class StateType>
struct EventActionStates
{
    typedef StateType state_type;
    bool finalize;
    bool doChangeAction;
    StateType* nextState;

    EventActionStates()
    : finalize(false)
    , doChangeAction(false)
    , nextState(0)
    {
    }

    EventActionStates(const EventActionStates<StateType>& rhs)
    : finalize(rhs.finalize)
    , doChangeAction(rhs.finalize)
    , nextState(rhs.nextState)
    {
    }

    EventActionStates& operator=(const EventActionStates<StateType>& rhs)
    {
        finalize = rhs.finalize;
        doChangeAction = rhs.finalize;
        nextState = rhs.nextState;
        return *this;
    }

    void reset()
    {
        finalize = false;
        doChangeAction = false;
        nextState = 0;
    }
};

ACTION_TEMPLATE( GuardCompareXY
               , HAS_2_TEMPLATE_PARAMS(typename, StateType, typename, FnCompare)
               , AND_3_VALUE_PARAMS(eventActionStates,doFinalize,nextStateResult))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(!eventActionStates->doChangeAction && FnCompare()(arg0->x(),arg0->y()))
    {
        if(doFinalize)
        {
            eventActionStates->finalize = true;
        }
        else
        {
            eventActionStates->nextState = nextStateResult;
        }
        eventActionStates->doChangeAction = true;
    }
}

ACTION_TEMPLATE( GuardCompareX
               , HAS_2_TEMPLATE_PARAMS(typename, StateType, typename, FnCompare)
               , AND_4_VALUE_PARAMS(eventActionStates,value,doFinalize,nextStateResult))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(!eventActionStates->doChangeAction && FnCompare()(arg0->x(),value))
    {
        if(doFinalize)
        {
            eventActionStates->finalize = true;
        }
        else
        {
            eventActionStates->nextState = nextStateResult;
        }
        eventActionStates->doChangeAction = true;
    }
}

ACTION_TEMPLATE( GuardCompareY
               , HAS_2_TEMPLATE_PARAMS(typename, StateType, typename, FnCompare)
               , AND_4_VALUE_PARAMS(eventActionStates,value,doFinalize,nextStateResult))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(!eventActionStates->doChangeAction && FnCompare()(arg0->y(),value))
    {
        if(doFinalize)
        {
            eventActionStates->finalize = true;
        }
        else
        {
            eventActionStates->nextState = nextStateResult;
        }
        eventActionStates->doChangeAction = true;
    }
}

ACTION_TEMPLATE( GuardCompareZ
               , HAS_2_TEMPLATE_PARAMS(typename, StateType, typename, FnCompare)
               , AND_4_VALUE_PARAMS(eventActionStates,value,doFinalize,nextStateResult))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(!eventActionStates->doChangeAction && FnCompare()(arg0->z(),value))
    {
        if(doFinalize)
        {
            eventActionStates->finalize = true;
        }
        else
        {
            eventActionStates->nextState = nextStateResult;
        }
        eventActionStates->doChangeAction = true;
    }
}

ACTION_TEMPLATE( EventDefaultAction
               , HAS_1_TEMPLATE_PARAMS(typename, StateType)
               , AND_3_VALUE_PARAMS(eventActionStates,doFinalize,nextStateResult))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(!eventActionStates->doChangeAction)
    {
        if(doFinalize)
        {
            eventActionStates->finalize = true;
            eventActionStates->doChangeAction = true;
        }
        else if(nextStateResult)
        {
            eventActionStates->nextState = nextStateResult;
            eventActionStates->doChangeAction = true;
        }
    }
}

ACTION_TEMPLATE( PerformStateChangeOrFinalize
               , HAS_1_TEMPLATE_PARAMS(typename, StateType)
               , AND_2_VALUE_PARAMS(currentStateMock,eventActionStates))
{
    ::testing::StaticAssertTypeEq<EventActionStates<StateType>*,eventActionStates_type>();
    if(eventActionStates->doChangeAction)
    {
        if(eventActionStates->finalize)
        {
            arg0->finalize();
        }
        else if(eventActionStates->nextState)
        {
            currentStateMock->doStateChange(arg0,eventActionStates->nextState);
        }
    }
}

ACTION_P(PropagateEvent1,compositeState)
{
    compositeState->propagateEvent1(arg0);
}

ACTION_P(PropagateEvent2,compositeState)
{
    compositeState->propagateEvent2(arg0);
}

ACTION_P(PropagateEvent3,compositeState)
{
    compositeState->propagateEvent3(arg0);
}


ACTION_P(PropagateEvent4,compositeState)
{
    compositeState->propagateEvent4(arg0);
}

ACTION_P(PropagateEvent5,compositeState)
{
    compositeState->propagateEvent5(arg0);
}
#endif /* DEMO3BACTIONDEFINITIONS_H_ */
