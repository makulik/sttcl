/*
 * ConcurrentCompositeState.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef CONCURRENTCOMPOSITESTATE_H_
#define CONCURRENTCOMPOSITESTATE_H_

#include "CompositeState.h"
#include "Region.h"

namespace sttcl
{

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
, unsigned int NumOfRegions = 1
, class EventArgs = void
, class StateBaseImpl = State<CompositeStateImpl,StateMachineImpl,typename StateMachineImpl::StateInterface>
>
class ConcurrentCompositeState
: public StateBaseImpl
{
public:

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
	typedef RegionBase<StateMachineImpl,StateInterface> RegionBaseType;
	/**
	 * The type of the regions array.
	 */
	typedef RegionBaseType* RegionsArray[NumOfRegions];
    /**
     * The context state machine implementation type.
     */
	typedef StateMachineImpl Context;
	/**
	 * The inner states event handler signature. All methods of the IInnerState interface
	 * must have this signature. The first parameter is a pointer to the containing state
	 * machine. The second parameter is a pointer to additional event arguments as specified
	 * with the EventArgs template parameter.
	 */
	typedef void (StateInterface::*EventHandler)(Context*,EventArgs const*);

	/**
	 * Constructor for class ConcurrentCompositeState.
	 * @param argRegions A reference to the concrete array of regions in the concurrent composite
	 *                   state.
	 */
	ConcurrentCompositeState(const RegionsArray& argRegions)
	: regions(argRegions)
	{
	}

	/**
	 * Destructor for class ConcurrentCompositeState.
	 */
	virtual ~ConcurrentCompositeState()
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
			if(regions[i]->isRegionInitialized())
			{
				regions[i]->enterRegion(context);
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
			if(regions[i]->isRegionInitialized())
			{
				regions[i]->exitRegion(context);
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
			if(!regions[i]->initializeRegion(recursive))
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
			if(!regions[i]->isRegionFinalized())
			{
				regions[i]->finalizeRegion(recursive);
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
			regions[i]->startDoRegion(context);
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
			if(regions[i]->isRegionThreadRunning())
			{
				regions[i]->endDoRegion(context);
			}
		}
    }

protected:

    /**
     * Broadcasts an event to all contained regions.
     * @param context A pointer to the containing state machine.
     * @param eventHandler The event handler to call inside all region threads.
     * @param eventArgs The event arguments to pass to the event handler calls.
     */
	void broadcastEvent(Context* context,EventHandler eventHandler,const EventArgs* eventArgs = 0)
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

private:
	const RegionsArray& regions;
};

}

#endif /* CONCURRENTCOMPOSITESTATE_H_ */
