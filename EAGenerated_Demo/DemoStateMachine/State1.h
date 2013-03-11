///////////////////////////////////////////////////////////
//  State1.h
//  Implementation of the Class State1
//  Created on:      17-Jul-2012 22:48:05
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_337FBF19_7860_4e87_A4D8_425428344D15__INCLUDED_)
#define EA_337FBF19_7860_4e87_A4D8_425428344D15__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "DemoStateMachine.h"
// Forward declarations from state diagram (SttclState)

class State1
: public sttcl::State<State1,DemoStateMachine,IInnerEvents >
{

public:
	typedef sttcl::State<State1,DemoStateMachine,IInnerEvents > StateBaseClass;

	virtual ~State1();
	void entryImpl(DemoStateMachine* context);
	static State1& getInstance();
	virtual void handleEvent1(DemoStateMachine* context, int p1, std::string& p2);
	virtual void handleEvent2(DemoStateMachine* context, double p1, double p2);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3);

private:
	State1();

};
#endif // !defined(EA_337FBF19_7860_4e87_A4D8_425428344D15__INCLUDED_)
