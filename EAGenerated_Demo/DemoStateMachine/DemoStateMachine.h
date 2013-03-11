///////////////////////////////////////////////////////////
//  DemoStateMachine.h
//  Implementation of the Class DemoStateMachine
//  Created on:      17-Jul-2012 22:48:00
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_010EE4E0_D484_4418_99D0_651F50ED1BCE__INCLUDED_)
#define EA_010EE4E0_D484_4418_99D0_651F50ED1BCE__INCLUDED_

// EA generated imports
#include <StateMachine.h>
#include <State.h>
// Sttcl generated imports
#include "IInnerEvents.h"

// Forward declarations from state diagram (SttclStateMachine)
class State2;
class State3;

class DemoStateMachine
: public sttcl::StateMachine<DemoStateMachine,IInnerEvents >
{

public:
	typedef sttcl::StateMachine<DemoStateMachine,IInnerEvents > StateMachineBase;

	typedef sttcl::StateBase<DemoStateMachine,IInnerEvents > StateBaseClass;


	DemoStateMachine();
	virtual ~DemoStateMachine();
	int x;
	int y;

	void event1(int p1, std::string& p2);
	void event2(double p1, double p2);
	void event3();
	void event4(int p1, long p2, std::vector<int>& p3);
	DemoStateMachine::StateBaseClass* getInitialStateImpl() const;
	State2& getState2() const;
	State3& getState3() const;
	int getX();
	int getY();

private:
	State2* state2;
	State3* state3;

};
#endif // !defined(EA_010EE4E0_D484_4418_99D0_651F50ED1BCE__INCLUDED_)
