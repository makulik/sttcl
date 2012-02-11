/*
 * DemoState3.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3_H_
#define DEMOSTATE3_H_

#include "IDemoState.h"
#include "ActiveState.h"

namespace Application
{

class DemoState3
: public sttcl::ActiveState<DemoState3,DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::ActiveState<DemoState3,DemoStateMachine,IDemoState> StateBaseClass;

	DemoState3();
	virtual ~DemoState3();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

    bool checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, StateBase<DemoStateMachine,IDemoState>*& nextState);

private:
	void doAction(DemoStateMachine* context, bool firstCall);

};

}

#endif /* DEMOSTATE3_H_ */
