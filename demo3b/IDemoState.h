/*
 * IDemoState.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef IDEMOSTATE_H_
#define IDEMOSTATE_H_

namespace Application
{

class DemoStateMachine;

class IDemoState
{
public:
	virtual void handleEvent1(DemoStateMachine* context) = 0;
	virtual void handleEvent2(DemoStateMachine* context) = 0;
	virtual void handleEvent3(DemoStateMachine* context) = 0;
	virtual void handleEvent4(DemoStateMachine* context) = 0;
	virtual void handleEvent5(DemoStateMachine* context) = 0;
	virtual ~IDemoState() {}
};

}

#endif /* IDEMOSTATE_H_ */
