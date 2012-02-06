/*
 * DemoState2.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE2_H_
#define DEMOSTATE2_H_

#include "IDemoState.h"
#include "State.h"

namespace Application
{

class DemoState2
: public sttcl::State<DemoState2,DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::State<DemoState2,DemoStateMachine,IDemoState> StateBaseClass;

	DemoState2();
	virtual ~DemoState2();

	virtual void handleEvent1(DemoStateMachine* context);
	virtual void handleEvent2(DemoStateMachine* context);
	virtual void handleEvent3(DemoStateMachine* context);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

	static DemoState2& getInstance();

};

}

#endif /* DEMOSTATE2_H_ */
