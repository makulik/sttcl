/*
 * main.cpp
 *
 *  Created on: 11.12.2011
 *      Author: Admin
 */

#include <iostream>
#include "../DemoStateMachine.h"
#include "../CmdInterpreter.h"

using namespace std;

int main(int argc, char** argv)
{
	Application::DemoStateMachine demoStateMachine;
	Application::CmdInterpreter cmdInterpreter(cin,demoStateMachine);

    return cmdInterpreter.run();
}
