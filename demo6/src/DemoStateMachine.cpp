/*
 * DemoStateMachine.cpp
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#include <iostream>

#include "../ConcurrentStateMachine.h"
#include "../CmdInterpreter.h"
#include "../DemoStateMachine.h"
#include "../InputEvent.h"
#include "../SubStateMachineCompletedEvent.h"

using namespace std;
using namespace Application;
using namespace sttcl;
using namespace sttcl::internal;

using Application::DemoStateMachine;

DemoStateMachine::DemoStateMachine()
: thread(this,&DemoStateMachine::threadMethod)
, eventQueue()
, concurrentStateMachine(new ConcurrentStateMachine(this))
, cmdInterpreter(new CmdInterpreter(this))
, threadMutex()
, terminated(false)
{
}

DemoStateMachine::~DemoStateMachine()
{
	delete concurrentStateMachine;
	delete cmdInterpreter;
}

void DemoStateMachine::run()
{
	thread.run();
}

void DemoStateMachine::sendEvent(const EventPtr& event)
{
	eventQueue.push_back(event);
}

bool DemoStateMachine::isTerminationCmd(const std::string& cmd)
{
	return cmdInterpreter->isTerminationCmd(cmd);
}

bool DemoStateMachine::isTerminated()
{
	AutoLocker<SttclMutex<> > lock(threadMutex);
	return terminated;
}

void DemoStateMachine::waitForTermination()
{
	thread.join();
}

void DemoStateMachine::event1(const EventPtr& event)
{
	cout << "DemoStateMachine, event1 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent1(this,event);
	}
}

void DemoStateMachine::event2(const EventPtr& event)
{
	cout << "DemoStateMachine, event2 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent2(this,event);
	}
}

void DemoStateMachine::event3(const EventPtr& event)
{
	cout << "DemoStateMachine, event3 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent3(this,event);
	}
}

void DemoStateMachine::event4(const EventPtr& event)
{
	cout << "DemoStateMachine, event4 triggered ..." << endl;
	StateMachineBase::StateBaseClass* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent4(this,event);
	}
}

void DemoStateMachine::subStateMachineCompletedImpl(StateMachineBase::StateBaseClass* state)
{
	if(!isFinalizing())
	{
		cout << "DemoStateMachine, sub statemachine completed ..." << endl;
		StateMachineBase::subStateMachineCompletedImpl(state);
		DemoStateMachine::EventPtr subStateMachineEcompletedEvent(new SubStateMachineCompletedEvent());
		sendEvent(subStateMachineEcompletedEvent);
	}
}

sttcl::StateBase<DemoStateMachine,IDemoState>* DemoStateMachine::getInitialStateImpl() const
{
	cout << "DemoStateMachine, returning initial state ..." << endl;
	return concurrentStateMachine;
}

void* DemoStateMachine::threadMethod(void* userArgs)
{
	cout << "DemoStateMachine, internal thread started ..." << endl;
	bool terminate = false;

	initialize();

	while(!terminate && !isFinalized())
	{
		if(eventQueue.waitForEvents())
		{
			if(!eventQueue.empty())
			{
				cout << "DemoStateMachine, received event ..." << endl;
				EventPtr eventPtr = eventQueue.front();
				eventQueue.pop_front();

				if(dynamic_cast<InputEvent*>(eventPtr.get()))
				{
					sttcl::RefCountPtr<InputEvent> inputEvent(eventPtr);
					cout << "Sending command from input '" << inputEvent->getInput() << "'" << std::endl;
					terminate = cmdInterpreter->sendCmd(inputEvent->getInput(),inputEvent);
				}
				else if(dynamic_cast<SubStateMachineCompletedEvent*>(eventPtr.get()))
				{
					sttcl::RefCountPtr<SubStateMachineCompletedEvent> subStateMachineCompletedEvent(eventPtr);
					cout << "DemoStateMachine, sub statemachine completed, finalizing ..." << endl;
					cout << "*** Press <ENTER> once more to end the program ***" << endl;
					finalize();
				}
			}
		}
	}

	{ AutoLocker<SttclMutex<> > lock(threadMutex);
		terminated = true;
	}

	cout << "DemoStateMachine, internal thread exiting ..." << endl;
	if(!isFinalized())
	{
		finalize();
	}

	return 0;
}
