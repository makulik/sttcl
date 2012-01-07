/*
 * Region.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGION_H_
#define REGION_H_

#include "CompositeState.h"
#include "ActiveState.h"
#include "SttclMutex.h"
#include "SttclSemaphore.h"
#include <deque>

namespace sttcl
{

template
< class StateMachineImpl
, class StateInterface
, class EventArgs = void
>
class RegionBase
{
public:
	RegionBase()
	{
	}
	~RegionBase()
	{
	}

    typedef void (StateInterface::*EventHandler)(StateMachineImpl*, const EventArgs*);


	virtual void handleBroadcastedEvent(StateMachineImpl* context,EventHandler eventHandler, const EventArgs* eventArgs) = 0;
	virtual void enterRegion(StateMachineImpl* context) = 0;
	virtual void exitRegion(StateMachineImpl* context) = 0;
	virtual void finalizeRegion(bool recursive) = 0;
	virtual bool initializeRegion(bool recursive) = 0;
	virtual void startDoRegion(StateMachineImpl* context) = 0;
	virtual void endDoRegion(StateMachineImpl* context) = 0;
	virtual bool isRegionFinalized() = 0;
	virtual void joinRegionThread() = 0;

	template<class RegionImpl>
	RegionImpl* getRegionContext()
	{
		return static_cast<RegionImpl*>(this);
	}
};

template
< class RegionImpl
, class StateMachineImpl
, class IInnerState
, class EventArgs = void
, CompositeStateHistoryType::Values HistoryType = CompositeStateHistoryType::None
>
class Region
: public CompositeState
  	< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
	, StateMachineImpl
	, IInnerState
	, HistoryType
	, ActiveState
		< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
		, StateMachineImpl
		, typename StateMachineImpl::StateInterface
		>
	, StateMachine<RegionImpl, IInnerState>
	>
, public RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs>
{
public:
	friend class RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs>;

    /**
     * The implementation class type.
     */
    typedef RegionImpl Implementation;

    /**
     * The state machine implementation type.
     */
    typedef StateMachineImpl Context;

    typedef CompositeState
    	  	< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
    		, StateMachineImpl
    		, IInnerState
    		, HistoryType
    		, ActiveState
    			< Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>
    			, StateMachineImpl
    			, typename StateMachineImpl::StateInterface
    			>
    		, StateMachine<RegionImpl, IInnerState>
    		> CompositeStateBase;
    typedef RegionBase<StateMachineImpl,typename StateMachineImpl::StateInterface,EventArgs> RegionBaseClass;

    typedef typename RegionBaseClass::EventHandler OuterEventHandler;

    typedef void (IInnerState::*InnerEventHandler)(RegionBaseClass*,const EventArgs*);

    typedef void (Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::*InternalEventHandler)(bool);

    typedef typename CompositeStateBase::StateImplementationBase StateImplementationBase;

    typedef typename CompositeStateBase::StateMachineImplementationBase StateMachineImplementationBase;

    /**
     * The state do action type.
     */
    typedef typename CompositeStateBase::StateDoAction StateDoAction;

    /**
     * The composite state base class regarding state history policy.
     */
	typedef typename CompositeStateBase::CompositeStateHistoryBaseClass CompositeStateHistoryBaseClass;

	/**
	 * The inner state class.
	 */
	typedef typename CompositeStateBase::InnerStateClass InnerStateClass;

	/**
	 * The outer state interface.
	 */
	typedef typename CompositeStateBase::OuterStateInterface OuterStateInterface;

	/**
	 * The state interface.
	 */
	typedef typename CompositeStateBase::StateInterface StateInterface;

	typedef StateBase<RegionImpl,IInnerState> RegionStateBase;

	typedef RegionStateBase StateBaseClass;

    typedef typename StateImplementationBase::StateThreadImpl RegionThreadImpl;

	Region(sttcl::TimeDuration<> argDoActionFrequency = sttcl::TimeDuration<>::Zero)
	: CompositeStateBase(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::regionDoAction)
	, eventsAvailable(0)
	, checkEventFrequency(argDoActionFrequency)
	{
	}
	virtual ~Region()
	{
	}

	void dispatchEvent(IInnerState* state, InnerEventHandler eventHandler, const EventArgs* eventArgs)
	{
		AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
		eventDispatchQueue.push_back(DispatchedEvent(state,eventHandler,eventArgs));
		unblockEventsAvailable();
	}

	void dispatchInternalEvent(InternalEventHandler internalEventHandler, bool recursive)
	{
		AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
		eventDispatchQueue.push_back(DispatchedEvent(internalEventHandler,recursive));
		unblockEventsAvailable();
	}

	void changeState(RegionStateBase* newState)
	{
		StateMachineImplementationBase::changeState(newState);
	}

	void startingRegionThread()
	{

	}

	void endingRegionThread()
	{

	}

    void entryImpl(Context* context)
    {
    	CompositeStateBase::entryImpl(context);
    }

    void exitImpl(Context* context)
    {
    	CompositeStateBase::exitImpl(context);
    }

    bool initializeImpl(bool force)
    {
    	// dispatch initialization to region thread
    	dispatchInternalEvent(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::internalInitialize,force);
    	return true;
    }

    /**
     * Default implementation for finalize().
     *
     * @param finalizeSubStateMachines Indicates to finalize any sub state machines.
     */
    inline void finalizeImpl(bool finalizeSubStateMachines)
    {
    	// dispatch finalization to region thread
    	dispatchInternalEvent(&Region<RegionImpl,StateMachineImpl,IInnerState,EventArgs,HistoryType>::internalFinalize,finalizeSubStateMachines);
    }

    bool endDoActionRequestedImpl()
    {
    	return //static_cast<StateMachineImplementationBase*>(this)->isFinalized() ||
    		   static_cast<StateImplementationBase*>(this)->endDoActionRequestedImpl();
    }

    void exitingDoActionImpl()
    {
		static_cast<RegionImpl*>(this)->endingRegionThread();
    }

    void joinDoActionThreadImpl()
    {
		static_cast<StateImplementationBase*>(this)->joinDoActionThreadImpl();
    }

    void unblockDoActionImpl()
    {
 		static_cast<StateImplementationBase*>(this)->unblockDoActionImpl();
		unblockEventsAvailable();
    }

    void endDoImpl(StateMachineImpl* context)
    {
	   if(!RegionThreadImpl::isSelf(static_cast<StateImplementationBase*>(this)->getStateThread()))
	   {
		   static_cast<StateImplementationBase*>(this)->endDoImpl(context);
	   }
    }
private:
	virtual void handleBroadcastedEvent(StateMachineImpl* context,OuterEventHandler eventHandler, const EventArgs* eventArgs)
	{
		(static_cast<Implementation*>(this)->*eventHandler)(context,eventArgs);
	}

	virtual void enterRegion(StateMachineImpl* context)
	{
		static_cast<RegionImpl*>(this)->entryImpl(context);
	}

	virtual void exitRegion(StateMachineImpl* context)
	{
		static_cast<RegionImpl*>(this)->exitImpl(context);
	}

	virtual void startDoRegion(StateMachineImpl* context)
	{
		if(static_cast<RegionImpl*>(this)->isReady())
		{
			static_cast<RegionImpl*>(this)->startingRegionThread();
			static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->startDo(context);
		}
	}

	virtual void endDoRegion(StateMachineImpl* context)
	{
		if(static_cast<RegionImpl*>(this)->isReady())
		{
			static_cast<StateBase<StateMachineImpl,OuterStateInterface>*>(this)->endDo(context);
		}
	}

	virtual void finalizeRegion(bool recursive)
	{
		static_cast<RegionImpl*>(this)->finalize(recursive);
	}

	virtual bool initializeRegion(bool recursive)
	{
		static_cast<RegionImpl*>(this)->initialize(recursive);
		return static_cast<RegionImpl*>(this)->isReady();
	}

	virtual bool isRegionFinalized()
	{
		return static_cast<RegionImpl*>(this)->isFinalized();
	}

	virtual void joinRegionThread()
	{
		return static_cast<RegionImpl*>(this)->joinDoActionThreadImpl();
	}

	void internalInitialize(bool recursive)
	{
    	static_cast<StateMachineImplementationBase*>(this)->initializeImpl(recursive);
	}

	void internalFinalize(bool recursive)
	{
    	static_cast<StateMachineImplementationBase*>(this)->finalizeImpl(recursive);
	}

	struct DispatchedEvent
	{
		IInnerState* state;
		InnerEventHandler handler;
		const EventArgs* eventArgs;
		InternalEventHandler internalHandler;
		bool recursiveInternalEvent;

		DispatchedEvent(IInnerState* argState, InnerEventHandler argHandler, const EventArgs* argEventArgs)
		: state(argState)
		, handler(argHandler)
		, eventArgs(argEventArgs)
		, internalHandler(0)
		, recursiveInternalEvent(false)
		{
		}

		DispatchedEvent(InternalEventHandler argInternalHandler, bool argRecursiveInternalEvent)
		: state(0)
		, handler(0)
		, eventArgs(0)
		, internalHandler(argInternalHandler)
		, recursiveInternalEvent(argRecursiveInternalEvent)
		{
		}

		DispatchedEvent(const DispatchedEvent& rhs)
		: state(rhs.state)
		, handler(rhs.handler)
		, eventArgs(rhs.eventArgs)
		, internalHandler(rhs.internalHandler)
		, recursiveInternalEvent(rhs.recursiveInternalEvent)
		{
		}
	};

	void unblockEventsAvailable()
	{
		eventsAvailable.post();
	}

	bool checkEventsAvailable()
	{
		return eventsAvailable.try_wait(checkEventFrequency);
	}

	void regionDoAction(Context* context, bool firstCall)
	{
		if(checkEventsAvailable())
		{
			AutoLocker<SttclMutex<> > lock(eventDispatchMutex);
			while(!eventDispatchQueue.empty())
			{
				DispatchedEvent dispatchedEvent = eventDispatchQueue.front();
				eventDispatchQueue.pop_front();
				if(dispatchedEvent.internalHandler)
				{
					(this->*dispatchedEvent.internalHandler)(dispatchedEvent.recursiveInternalEvent);
				}
				else
				{
					(dispatchedEvent.state->*dispatchedEvent.handler)(this,dispatchedEvent.eventArgs);
				}
			}
		}
	}

	SttclMutex<> eventDispatchMutex;
	SttclSemaphore<> eventsAvailable;
	std::deque<DispatchedEvent> eventDispatchQueue;
	sttcl::TimeDuration<> checkEventFrequency;
};

}

#endif /* REGION_H_ */
