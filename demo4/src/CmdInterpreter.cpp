/*
 * CmdInterpreter.cpp
 *
 *  Created on: 13.12.2011
 *      Author: Admin
 */

#include <sstream>
#include "../CmdInterpreter.h"
//#include <boost/thread.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace Application;
using Application::CmdInterpreter;

CmdInterpreter::CmdInterpreter(std::istream& argInput, DemoStateMachine& argStateMachine)
: input(argInput)
, stateMachine(argStateMachine)
{
}

CmdInterpreter::~CmdInterpreter()
{
}

int CmdInterpreter::run()
{
	string cmd;
	vector<string> cmdParts;
	bool exit = false;
	int result = 0;

	stateMachine.initialize();

	do
	{
		cout << "> ";
		cout.flush();
		getline(input,cmd);
		splitCmdLine(cmd,cmdParts);
		if(!cmdParts.empty())
		{
			if((cmdParts[0] == "exit") || (cmdParts[0] == "x"))
			{
				stateMachine.finalize(true);
				exit = true;
			}
			else if((cmdParts[0] == "help") || (cmdParts[0] == "h") || (cmdParts[0] == "?"))
			{
				printHelp();
			}
			else if((cmdParts[0] == "init") || (cmdParts[0] == "i"))
			{
				stateMachine.initialize(true);
			}
			else if((cmdParts[0] == "event") || (cmdParts[0] == "e"))
			{
				bool error = false;
				if(cmdParts.size() > 1)
				{
					istringstream istr(cmdParts[1]);
					int event;
					istr >> event;
					if(!istr.fail())
					{
						triggerEvent(event);
					}
					else
					{
						error = true;
					}
				}
				else
				{
					error = true;
				}
				if(error)
				{
					cerr << "Error: Command 'event' requires an event number." << endl;
				}
			}
			else if((cmdParts[0] == "set") || (cmdParts[0] == "s"))
			{
				if(cmdParts.size() > 2)
				{
					setVar(cmdParts[1],cmdParts[2]);
				}
				else
				{
					cerr << "Error: Command 'set' requires a variable name and value." << endl;
				}
			}
			else if((cmdParts[0] == "get") || (cmdParts[0] == "g"))
			{
				if(cmdParts.size() > 1)
				{
					getVar(cmdParts[1]);
				}
				else
				{
					cerr << "Error: Command 'get' requires a variable name." << endl;
				}
			}
			else if(cmdParts[0] != "")
			{
				cerr << "Error: Unknown command '" << cmdParts[0] << "'." << endl;
			}
		}
	} while(!exit);

	return result;
}

void CmdInterpreter::splitCmdLine(const string& cmdLine, vector<string>& cmdParts)
{
	cmdParts.clear();
	istringstream istr(cmdLine);

	while(!istr.eof())
	{
		string part;
		istr >> part;
		cmdParts.push_back(part);
	}
}

void CmdInterpreter::triggerEvent(int event)
{
	if(!stateMachine.isFinalized())
	{
		switch(event)
		{
		case 1:
			stateMachine.event1();
			break;
		case 2:
			stateMachine.event2();
			break;
		case 3:
			stateMachine.event3();
			break;
		case 4:
			stateMachine.event4();
			break;
		default:
			cerr << "Error: Unknown event number '" << event << "'." << endl;
			break;
		}
	}
	if(stateMachine.isFinalized())
	{
		cout << "State machine is finalized" << endl;
	}
}
void CmdInterpreter::setVar(const std::string& var, const std::string& value)
{
}
void CmdInterpreter::getVar(const std::string& var)
{
	cerr << "Error: Unknown variable '" << var << "'." << endl;
}

void CmdInterpreter::printHelp()
{
	cout << "Available commands:" << endl;
	cout << "exit | x              , exit the program" << endl;
	cout << "init | i              , initialize state machine" << endl;
	cout << "event | e <n>         , trigger event <n>" << endl;
	cout << "set | s <var> <value> , set variable" << endl;
	cout << "get | g <var>         , show variable" << endl;
	cout << "help | h | ?          , show help" << endl;
}
