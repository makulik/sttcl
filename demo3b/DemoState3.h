/*
 * DemoState3.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3_H_
#define DEMOSTATE3_H_

#include "IDemoState.h"
#include "IDemoState3.h"
#include "CompositeState.h"
#include "DemoStateMachine.h"

namespace Application
{

class DemoState3b;

class DemoState3
: public sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3,sttcl::CompositeStateHistoryType::Deep>
{
public:
	typedef typename sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3,sttcl::CompositeStateHistoryType::Deep>::StateBaseClass InnerStateBaseClass;
	typedef sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3,sttcl::CompositeStateHistoryType::Deep> StateBaseClass;

	DemoState3(DemoStateMachine* context);
	virtual ~DemoState3();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context);
	virtual void handleEvent5(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	InnerStateBaseClass* getInitialStateImpl() const;

	inline DemoStateMachine* getContext() const
	{
		return demoStateMachine;
	}

	int getX() const;
	int getY() const;
	int getZ() const;

	DemoState3b* getDemoState3b() const
	{
		return demoState3b;
	}

private:
	DemoStateMachine* demoStateMachine;
	DemoState3b* demoState3b;
};

}

#endif /* DEMOSTATE3_H_ */
