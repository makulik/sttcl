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
	typedef DemoStateMachine Context;

	virtual void handleEvent1(Context* context) = 0;
	virtual void handleEvent2(Context* context) = 0;
	virtual void handleEvent3(Context* context) = 0;
	virtual void handleEvent4(Context* context) = 0;
	virtual ~IDemoState() {}
};

}

#endif /* IDEMOSTATE_H_ */
