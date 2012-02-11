/*
 * DemoStateMachine.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATEMACHINE_H_
#define DEMOSTATEMACHINE_H_

#include "IDemoState.h"
#include "StateMachine.h"

namespace Application
{

class DemoStateMachine
: public sttcl::StateMachine<DemoStateMachine,IDemoState>
{
public:
	typedef sttcl::StateMachine<DemoStateMachine,IDemoState> StateMachineBase;

	DemoStateMachine();
	virtual ~DemoStateMachine();

	void event1();
	void event2();
	void event3();

	int getX() const
	{
		return x;
	}

	void setX(int value)
	{
		x = value;
	}

	int getY() const
	{
		return y;
	}

	void setY(int value)
	{
		y = value;
	}

    StateMachineBase::StateBaseClass* getInitialStateImpl() const;

private:
	int x;
	int y;
};

}

#endif /* DEMOSTATEMACHINE_H_ */
