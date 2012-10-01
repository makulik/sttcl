/**
 * @file ConcurrentCompositeState.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CONCURRENTCOMPOSITESTATE_H_
#define CONCURRENTCOMPOSITESTATE_H_

#include "CompositeState.h"
#include "Region.h"

namespace sttcl
{
namespace internal
{

template
< class CompositeStateImpl
, class IInnerState
, class EventArgs
>
class RegionContainer
{
public:
	/**
	 * The region base class type.
	 */
	typedef RegionBase<CompositeStateImpl,IInnerState,EventArgs> RegionBaseType;

	/**
	 * Destructor for the RegionContainer class.
	 */
	virtual ~RegionContainer() {}

    /**
     * Called when a region sub state machine completes (finalizes).
     * @param state A pointer to the finalized region.
     */
    virtual void regionCompleted(RegionBaseType* region) = 0;
};


template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class EventArgs
, class StateBaseImpl
>
class ConcurrentCompositeStateWithEventArgs
: public StateBaseImpl
{
public:
//    void changeStateImpl(StateMachineImpl* context,StateBaseImpl* newState)
//    {
//    	StateBaseImpl::changeState(context,newState);
//    }

protected:

	/**
	 * The region base class type.
	 */
	typedef RegionBase<CompositeStateImpl,IInnerState,EventArgs> RegionBaseType;
	/**
	 * The type of the regions array.
	 */
	typedef RegionBaseType* RegionsArray[NumOfRegions];

    /**
     * The context state machine implementation type.
     */
	typedef StateMachineImpl Context;

	typedef sttcl::internal::EventArgsInterfaceSelector<CompositeStateImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename StateMachineImpl::StateInterface OuterEventHandler;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	ConcurrentCompositeStateWithEventArgs(const RegionsArray& argRegions)
	: regions(argRegions)
	{
	}

    /**
     * Broadcasts an event to all contained regions.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside all region threads.
     * @param eventArgs The event arguments to pass to the event handler calls.
     */
	void broadcastEvent(Context* context,InnerEventHandler eventHandler,RefCountPtr eventArgs)
	{
		bool allRegionsFinalized = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!regions[i]->isRegionFinalized())
			{
				allRegionsFinalized = false;
				regions[i]->handleBroadcastedEvent(static_cast<CompositeStateImpl*>(this),eventHandler,eventArgs);
			}
			else
			{
				if(regions[i]->isRegionThreadRunning())
				{
					regions[i]->endDoRegion(static_cast<CompositeStateImpl*>(this));
					regions[i]->joinRegionThread();
				}
			}
		}
		if(allRegionsFinalized)
		{
			context->subStateMachineCompleted(this);
		}
	}

	const RegionsArray& regions;

};

template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class StateBaseImpl
>
class ConcurrentCompositeStateWithoutEventArgs
: public StateBaseImpl
{
public:
//    void changeStateImpl(StateMachineImpl* context,StateBaseImpl* newState)
//    {
//    	StateBaseImpl::changeState(context,newState);
//    }
protected:

	/**
	 * The region base class type.
	 */
	typedef RegionBase<CompositeStateImpl,IInnerState,void> RegionBaseType;

	/**
	 * The type of the regions array.
	 */
	typedef RegionBaseType* RegionsArray[NumOfRegions];

    /**
     * The context state machine implementation type.
     */
	typedef CompositeStateImpl Context;

	typedef sttcl::internal::EventArgsInterfaceSelector<CompositeStateImpl,IInnerState,void> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	ConcurrentCompositeStateWithoutEventArgs(const RegionsArray& argRegions)
	: regions(argRegions)
	{
	}

	/**
     * Broadcasts an event to all contained regions.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside all region threads.
     */
	void broadcastEvent(Context* context,InnerEventHandler eventHandler)
	{
		bool allRegionsFinalized = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!regions[i]->isRegionFinalized())
			{
				allRegionsFinalized = false;
				regions[i]->handleBroadcastedEvent(this,eventHandler);
			}
			else
			{
				if(regions[i]->isRegionThreadRunning())
				{
					regions[i]->endDoRegion(context);
					regions[i]->joinRegionThread();
				}
			}
		}
		if(allRegionsFinalized)
		{
			context->subStateMachineCompleted(this);
		}
	}

	const RegionsArray& regions;
};

/**
 * Used to select the region base implementation.
 * @tparam StateMachineImpl
 * @tparam StateInterface
 * @tparam EventArgs
 */
template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class EventArgs
, class StateBaseImpl
>
struct ConcurrentCompositeBaseImplementationSelector
{
	/**
	 * The region base implementation type.
	 */
	typedef ConcurrentCompositeStateWithEventArgs<CompositeStateImpl,StateMachineImpl,IInnerState,NumOfRegions,EventArgs,StateBaseImpl> RESULT_TYPE;

};

/**
 * Specializes RegionBaseImplementationSelector for void (i.e. no) event arguments.
 */
template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class StateBaseImpl
>
struct ConcurrentCompositeBaseImplementationSelector<CompositeStateImpl,StateMachineImpl,IInnerState,NumOfRegions,void,StateBaseImpl>
{
	/**
	 * The region base implementation type.
	 */
	typedef ConcurrentCompositeStateWithoutEventArgs<CompositeStateImpl,StateMachineImpl,IInnerState,NumOfRegions,StateBaseImpl> RESULT_TYPE;

};

/**
 * Represents a concurrent composite state implementation base class.
 * @tparam CompositeStateImpl
 * @tparam StateMachineImpl
 * @tparam IInnerState
 * @tparam NumOfRegions
 * @tparam EventArgs
 * @tparam StateBaseImpl
 */
template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class EventArgs
, class StateBaseImpl
>
class ConcurrentCompositeStateBase
: public ConcurrentCompositeBaseImplementationSelector
  	  < CompositeStateImpl
  	  , StateMachineImpl
  	  , IInnerState
  	  , NumOfRegions
  	  , EventArgs
  	  , StateBaseImpl
  	  >::RESULT_TYPE
, public RegionContainer<CompositeStateImpl,IInnerState,EventArgs>
{
public:
	typedef ConcurrentCompositeBaseImplementationSelector
		  	  < CompositeStateImpl
		  	  , StateMachineImpl
		  	  , IInnerState
		  	  , NumOfRegions
		  	  , EventArgs
		  	  , StateBaseImpl
		  	  > BaseClassSelectorType;

	typedef typename BaseClassSelectorType::RESULT_TYPE BaseClassType;

	/**
	 * The state implementation base class type.
	 */
    typedef StateBaseImpl StateImplementationBase;
	/**
	 * The (outer) state interface class type.
	 */
	typedef typename StateMachineImpl::StateInterface StateInterface;
	/**
	 * The state base class type.
	 */
	typedef typename StateMachineImpl::StateBaseClass StateBaseClass;
	/**
	 * The region base class type.
	 */
	typedef typename BaseClassType::RegionBaseType RegionBaseType;
	/**
	 * The type of the regions array.
	 */
	typedef typename BaseClassType::RegionsArray RegionsArray;
    /**
     * The context state machine implementation type.
     */
	typedef StateMachineImpl Context;

	typedef sttcl::internal::EventArgsInterfaceSelector<StateMachineImpl,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::RefCountPtr RefCountPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename StateMachineImpl::StateInterface OuterEventHandler;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	/**
	 * Constructor for class ConcurrentCompositeState.
	 * @param argRegions A reference to the concrete array of regions in the concurrent composite
	 *                   state.
	 */
    ConcurrentCompositeStateBase(Context* argContextStateMachine, const RegionsArray& argRegions)
	: BaseClassType(argRegions)
	, contextStateMachine(argContextStateMachine)
	{
	}

	/**
	 * Destructor for class ConcurrentCompositeState.
	 */
	virtual ~ConcurrentCompositeStateBase()
	{
	}

    /**
     * Default entry() implementation.
     *
     * @param context The state machine context.
     */
    inline void entryImpl(Context* context)
    {
    	StateImplementationBase::entryImpl(context);
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(BaseClassType::regions[i]->isRegionInitialized())
			{
				BaseClassType::regions[i]->enterRegion(static_cast<CompositeStateImpl*>(this));
			}
		}
    }

    /**
     * Default exit() implementation.
     *
     * @param context The state machine context.
     */
    inline void exitImpl(Context* context)
    {
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(BaseClassType::regions[i]->isRegionInitialized())
			{
				BaseClassType::regions[i]->exitRegion(static_cast<CompositeStateImpl*>(this));
			}
		}
    	StateImplementationBase::exitImpl(context);
    }

    /**
     * The StateBase::finalizeSubStateMachines() implementation.
     * @param recursive Indicates to finalize nested sub state machines recursively.
     */
    virtual void finalizeSubStateMachines(bool recursive)
    {
    	static_cast<CompositeStateImpl*>(this)->finalizeImpl(recursive);
    }

    /**
     * The StateBase::initSubStateMachines() implementation.
     * @param recursive Indicates to initialize nested sub state machines recursively.
     */
    virtual void initSubStateMachines(bool recursive)
    {
    	static_cast<CompositeStateImpl*>(this)->initializeImpl(recursive);
    }

    /**
     * The default initSubStateMachines() implementation.
     * @param recursive Indicates to initialize nested sub state machines recursively.
     * @return \c true if all contained regions were successfully initialized, \c false otherwise.
     */
    bool initializeImpl(bool recursive)
    {
    	bool result = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!BaseClassType::regions[i]->initializeRegion(recursive))
			{
				result = false;
			}
		}
    	return result;
    }

    void finalize(bool finalizeSubStateMachines = true)
    {
    	finalizeImpl(finalizeSubStateMachines);
    }

    /**
     * The default finalizeSubStateMachines() implementation.
     * @param recursive Indicates to finalize nested sub state machines recursively.
     */
    void finalizeImpl(bool recursive)
    {
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!BaseClassType::regions[i]->isRegionFinalized())
			{
				BaseClassType::regions[i]->finalizeRegion(recursive);
			}
		}
    }

    /**
     * Called after this state was entered.
     *
     * @param context The state machine context.
     */
    void startDoImpl(Context* context)
    {
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			BaseClassType::regions[i]->startDoRegion(static_cast<CompositeStateImpl*>(this));
		}
    }

    /**
     * Called before this state is left.
     *
     * @param context The state machine context.
     */
    void endDoImpl(Context* context)
    {
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(BaseClassType::regions[i]->isRegionThreadRunning())
			{
				BaseClassType::regions[i]->endDoRegion(static_cast<CompositeStateImpl*>(this));
			}
		}
    }

    /**
     * Called when a containe region is completed (finalized).
     * @param region The finalized region.
     */
    void regionCompletedImpl(RegionBaseType* region)
    {
    	bool allRegionsCompleted = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!BaseClassType::regions[i]->isRegionFinalized())
			{
				allRegionsCompleted = false;
			}
		}
		if(allRegionsCompleted)
		{
			contextStateMachine->subStateMachineCompleted(this);
		}
    }

    virtual Context* getContextStateMachine()
    {
    	return contextStateMachine;
    }

private:
    virtual void regionCompleted(RegionBaseType* region)
    {
    	static_cast<CompositeStateImpl*>(this)->regionCompletedImpl(region);
    }

    Context* contextStateMachine;
};

}

/**
 * Represents the base class for an orthogonal composite state implementation.
 * @tparam CompositeStateImpl The implementing class.
 * @tparam StateMachineImpl The containing state machine class.
 * @tparam IInnerState The inner state's interface class type.
 * @tparam NumOfRegions The number of orthogonal state regions (default is 1).
 * @tparam EventArgs The dispatch event arguments type (default is void).
 * @tparam StateBaseImpl The State class base implementation (default is
 *         State<CompositeStateImpl,StateMachineImpl,StateMachineImpl::StateInterface>)
 */
template
< class CompositeStateImpl
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions = 1
, class EventArgs = void
, class StateBaseImpl = State<CompositeStateImpl,StateMachineImpl,typename StateMachineImpl::StateInterface>
>
class ConcurrentCompositeState
: public sttcl::internal::ConcurrentCompositeStateBase
  	  	  < CompositeStateImpl
  	  	  , StateMachineImpl
  	  	  , IInnerState
  	  	  , NumOfRegions
  	  	  , EventArgs
  	  	  , StateBaseImpl
  	  	  >
{
public:
	typedef sttcl::internal::ConcurrentCompositeStateBase
	  	  	  < CompositeStateImpl
	  	  	  , StateMachineImpl
	  	  	  , IInnerState
	  	  	  , NumOfRegions
	  	  	  , EventArgs
	  	  	  , StateBaseImpl
	  	  	  > ConcurrenCompositeStateBaseType;

	typedef StateMachineImpl StateMachineClass;

	typedef typename ConcurrenCompositeStateBaseType::RegionBaseType RegionsBaseType;

	typedef typename ConcurrenCompositeStateBaseType::RegionsArray RegionsArray;

	typedef IInnerState InnerStateInterface;

	typedef typename StateMachineImpl::StateInterface OuterStateInterface;
	/**
	 * Constructor for class ConcurrentCompositeState.
	 * @param argRegions A reference to the concrete array of regions in the concurrent composite
	 *                   state.
	 */
	ConcurrentCompositeState(StateMachineImpl* context, const RegionsArray& argRegions)
	: ConcurrenCompositeStateBaseType(context,argRegions)
	{
	}

	/**
	 * Destructor for class ConcurrentCompositeState.
	 */
	virtual ~ConcurrentCompositeState()
	{
	}

    /**
     * Changes \em context state machine to another sibling state.
     * @param context A pointer to the containing state machine.
     * @param newState A pointer to the sibling state to change to.
     */
    void changeState(StateMachineImpl* context,sttcl::StateBase<StateMachineImpl,OuterStateInterface>* newState)
    {
    	static_cast<CompositeStateImpl*>(this)->changeStateImpl(context,newState);
    }

};
}

#endif /* CONCURRENTCOMPOSITESTATE_H_ */
