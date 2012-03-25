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

	do
	{
		if(!stateMachine.isInitialized())
		{
			continue;
		}
		if(!stateMachine.isTerminated())
		{
			cout << "> ";
			cout.flush();
			getline(input,cmd);
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
			exit = true;
		}
	} while(!exit);

	stateMachine.waitForTermination();

	return result;
}
