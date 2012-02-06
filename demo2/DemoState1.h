/*
 * DemoState1.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE1_H_
#define DEMOSTATE1_H_

#include "IDemoState.h"
#include "ActiveState.h"

namespace Application
{

class DemoState1
: public sttcl::ActiveState<DemoState1,DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::ActiveState<DemoState1,DemoStateMachine,IDemoState> StateBaseClass;

	DemoState1();
	virtual ~DemoState1();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

private:
	void doAction(DemoStateMachine* context, bool initialCall);

};

}

#endif /* DEMOSTATE1_H_ */
