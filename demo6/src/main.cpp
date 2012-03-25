/*
 * main.cpp
 *
 *  Created on: 11.12.2011
 *      Author: Admin
 */

#include <iostream>
#include "../DemoStateMachine.h"
#include "../CmdInterpreter.h"
#include "../MainApplication.h"

using namespace std;

int main(int argc, char** argv)
{
	Application::DemoStateMachine demoStateMachine;
	Application::MainApplication mainApplication(cin,demoStateMachine);

    return mainApplication.run();
}
