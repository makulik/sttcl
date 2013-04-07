/*
 * MainApplication.cpp
 *
 *  Created on: 22.03.2012
 *      Author: Admin
 */

#include "../MainApplication.h"
#include "../InputEvent.h"

using namespace std;
using namespace Application;

MainApplication::MainApplication(istream& argInput, DemoStateMachine& argStateMachine)
: input(argInput)
, stateMachine(argStateMachine)
{
}

MainApplication::~MainApplication()
{
}

int MainApplication::run()
{
	string cmd;
	bool exit = false;
	int result = 0;

	stateMachine.run();

	// Ideally the following part should be kind of an event poll loop, that allows
	// to check for either input or state machine termination from state machine internal
	// processing.
	do
	{
		if(!stateMachine.isInitialized())
		{
			continue;
		}

		cout << "> ";
		cout.flush();
		getline(input,cmd);
		if(!stateMachine.isTerminated())
		{
			if(!cmd.empty())
			{
				DemoStateMachine::EventPtr inputEvent(new InputEvent(cmd));
				stateMachine.sendEvent(inputEvent);
				if(stateMachine.isTerminationCmd(cmd))
				{
					exit = true;
				}
			}
		}
		else
		{
			cout << "State machine was terminated ..." << endl;
			stateMachine.waitForTermination();
			exit = true;
		}
	} while(!exit);

	return result;
}
