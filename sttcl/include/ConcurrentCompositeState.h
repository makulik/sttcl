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

    typedef StateBaseImpl StateImplementationBase;
	typedef typename StateMachineImpl::StateInterface StateInterface;
	typedef typename StateMachineImpl::StateBaseClass StateBaseClass;
	typedef RegionBase<StateMachineImpl,StateInterface> RegionBaseType;
	typedef RegionBaseType* RegionsArray[NumOfRegions];
	typedef StateMachineImpl Context;
	typedef void (StateInterface::*EventHandler)(Context*,EventArgs const*);

	ConcurrentCompositeState(const RegionsArray& argRegions)
	: regions(argRegions)
	{
	}

	virtual ~ConcurrentCompositeState()
	{
	}

    /**
     * Default enter() implementation.
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

    virtual void finalizeSubStateMachines(bool recursive)
    {
    	static_cast<CompositeStateImpl*>(this)->finalizeImpl(recursive);
    }

    virtual void initSubStateMachines(bool recursive)
    {
    	static_cast<CompositeStateImpl*>(this)->initializeImpl(recursive);
    }

    bool initializeImpl(bool recursive)
    {
		for(unsigned int i = 0; i < NumOfRegions; ++i)
		{
			regions[i]->initializeRegion(recursive);
		}
    	return true;
    }

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
