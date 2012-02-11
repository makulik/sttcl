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
	CmdInterpreter(std::istream& argInput, DemoStateMachine& argStateMachine);
	virtual ~CmdInterpreter();

	int run();

private:
	std::istream& input;
	DemoStateMachine& stateMachine;

	void splitCmdLine(const std::string& cmdLine,std::vector<std::string>& cmdParts);
	void triggerEvent(int event);
	void setVar(const std::string& var, const std::string& value);
	void getVar(const std::string& var);
	void printHelp();

};
}
#endif /* CMDINTERPRETER_H_ */
