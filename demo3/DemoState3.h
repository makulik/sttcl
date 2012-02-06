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

class DemoState3
: public sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3>
{
public:
	typedef sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3>::StateBaseClass InnerStateBaseClass;
	typedef sttcl::CompositeState<DemoState3,DemoStateMachine,IDemoState3> StateBaseClass;

	DemoState3(DemoStateMachine* context);
	virtual ~DemoState3();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context);
	virtual void handleEvent5(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);
	InnerStateBaseClass* getInitialStateImpl() const;

	inline DemoStateMachine* getContext() const
	{
		return demoStateMachine;
	}

	int getX() const;
	int getY() const;
	int getZ() const;

private:
	DemoStateMachine* demoStateMachine;
};

}

#endif /* DEMOSTATE3_H_ */
