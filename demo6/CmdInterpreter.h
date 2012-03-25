/*
 * CmdInterpreter.h
 *
 *  Created on: 13.12.2011
 *      Author: Admin
 */

#ifndef CMDINTERPRETER_H_
#define CMDINTERPRETER_H_

#include <iostream>
#include <string>
#include <vector>
#include "DemoStateMachine.h"

namespace Application
{

class CmdInterpreter
{
public:
	CmdInterpreter(DemoStateMachine* argStateMachine);
	virtual ~CmdInterpreter();

	bool sendCmd(const std::string& cmd);
	bool isTerminationCmd(const std::string& cmd);

private:
	DemoStateMachine* stateMachine;

	void splitCmdLine(const std::string& cmdLine,std::vector<std::string>& cmdParts);
	void triggerEvent(int event);
	void setVar(const std::string& var, const std::string& value);
	void getVar(const std::string& var);
	void printHelp();

};
}
#endif /* CMDINTERPRETER_H_ */
