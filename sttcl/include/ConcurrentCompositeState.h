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
, class StateMachineImpl
, class IInnerState
, unsigned int NumOfRegions
, class EventArgs
, class StateBaseImpl
>
class ConcurrentCompositeStateWithEventArgs
: public StateBaseImpl
{
protected:

	/**
	 * The region base class type.
	 */
	typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> RegionBaseType;
	/**
	 * The type of the regions array.
	 */
	typedef RegionBaseType* RegionsArray[NumOfRegions];

    /**
     * The context state machine implementation type.
     */
	typedef StateMachineImpl Context;

	typedef sttcl::internal::EventArgsInterfaceSelector<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

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
	void broadcastEvent(Context* context,OuterEventHandler eventHandler,EventArgsPtr eventArgs)
	{
		bool allRegionsFinalized = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!regions[i]->isRegionFinalized())
			{
				allRegionsFinalized = false;
				regions[i]->handleBroadcastedEvent(context,eventHandler,eventArgs);
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
protected:
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
protected:

	/**
	 * The region base class type.
	 */
	typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,void> RegionBaseType;

	/**
	 * The type of the regions array.
	 */
	typedef RegionBaseType* RegionsArray[NumOfRegions];

    /**
     * The context state machine implementation type.
     */
	typedef StateMachineImpl Context;

	typedef sttcl::internal::EventArgsInterfaceSelector<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,void> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

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
	void broadcastEvent(Context* context,OuterEventHandler eventHandler)
	{
		bool allRegionsFinalized = true;
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			if(!regions[i]->isRegionFinalized())
			{
				allRegionsFinalized = false;
				regions[i]->handleBroadcastedEvent(context,eventHandler);
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

protected:
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

	typedef sttcl::internal::EventArgsInterfaceSelector<StateMachineImpl,typename StateMachineImpl::StateInterface,IInnerState,EventArgs> EventArgsSelectorType;

	/**
	 * The pointer type used to pass event arguments to the contained regions inner states.
	 */
	typedef typename EventArgsSelectorType::EventArgsPtr EventArgsPtr;

	/**
     * The outer event handler signature.
     */
	typedef typename EventArgsSelectorType::OuterEventHandler OuterEventHandler;

	/**
     * The inner event handler signature.
     */
	typedef typename EventArgsSelectorType::InnerEventHandler InnerEventHandler;

	/**
	 * Constructor for class ConcurrentCompositeState.
	 * @param argRegions A reference to the concrete array of regions in the concurrent composite
	 *                   state.
	 */
    ConcurrentCompositeStateBase(const RegionsArray& argRegions)
	: BaseClassType(argRegions)
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
				BaseClassType::regions[i]->enterRegion(context);
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
				BaseClassType::regions[i]->exitRegion(context);
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
			BaseClassType::regions[i]->startDoRegion(context);
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
				BaseClassType::regions[i]->endDoRegion(context);
			}
		}
    }
};

}

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

	typedef typename ConcurrenCompositeStateBaseType::RegionBaseType RegionsBaseType;

	typedef typename ConcurrenCompositeStateBaseType::RegionsArray RegionsArray;

	typedef IInnerState InnerStateInterface;
	/**
	 * Constructor for class ConcurrentCompositeState.
	 * @param argRegions A reference to the concrete array of regions in the concurrent composite
	 *                   state.
	 */
	ConcurrentCompositeState(const RegionsArray& argRegions)
	: ConcurrenCompositeStateBaseType(argRegions)
	{
	}

	/**
	 * Destructor for class ConcurrentCompositeState.
	 */
	virtual ~ConcurrentCompositeState()
	{
	}
};
}

#endif /* CONCURRENTCOMPOSITESTATE_H_ */
