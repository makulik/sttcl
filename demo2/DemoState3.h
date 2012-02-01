/*
 * DemoState3.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3_H_
#define DEMOSTATE3_H_

#include "IDemoState.h"
#include "State.h"

namespace Application
{

class DemoState3
: public sttcl::State<DemoState3,DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::State<DemoState3,DemoStateMachine,IDemoState> StateBaseClass;

	DemoState3();
	virtual ~DemoState3();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

	static DemoState3& getInstance();

private:
	void doAction(DemoStateMachine* context, bool firstCall);

};

}

#endif /* DEMOSTATE3_H_ */
