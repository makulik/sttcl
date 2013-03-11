///////////////////////////////////////////////////////////
//  State2.h
//  Implementation of the Class State2
//  Created on:      17-Jul-2012 22:48:06
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_6A4CB100_6F21_4a28_AB86_282F50C53398__INCLUDED_)
#define EA_6A4CB100_6F21_4a28_AB86_282F50C53398__INCLUDED_

// EA generated imports
#include <ActiveState.h>
// Sttcl generated imports
#include "DemoStateMachine.h"

// Forward declarations from state diagram (SttclActiveState)

class State2
: public sttcl::ActiveState<State2,DemoStateMachine,IInnerEvents >
{

public:
	typedef sttcl::ActiveState<State2,DemoStateMachine,IInnerEvents > StateBaseClass;
	int z;

	State2();
	virtual ~State2();
	bool checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState);
	virtual void handleEvent1(DemoStateMachine* context, int p1, std::string& p2);
	virtual void handleEvent2(DemoStateMachine* context, double p1, double p2);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3);
	int Z();

private:
	void doAction(DemoStateMachine* context, bool initialCall);

};
#endif // !defined(EA_6A4CB100_6F21_4a28_AB86_282F50C53398__INCLUDED_)
