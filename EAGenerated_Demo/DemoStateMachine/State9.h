///////////////////////////////////////////////////////////
//  State9.h
//  Implementation of the Class State9
//  Created on:      17-Jul-2012 22:48:18
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_F1E8554A_12F1_4c6d_A86B_CA0B25C4A8F6__INCLUDED_)
#define EA_F1E8554A_12F1_4c6d_A86B_CA0B25C4A8F6__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "DemoStateMachine.h"

// Forward declarations from state diagram (SttclState)
class State9
: public sttcl::State<State9,DemoStateMachine,IInnerEvents >
{

public:
	typedef sttcl::State<State9,DemoStateMachine,IInnerEvents > StateBaseClass;

	virtual ~State9();
	bool checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState);
	static State9& getInstance();
	virtual void handleEvent1(DemoStateMachine* context, int p1, std::string& p2);
	virtual void handleEvent2(DemoStateMachine* context, double p1, double p2);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3);

private:
	State9();

};
#endif // !defined(EA_F1E8554A_12F1_4c6d_A86B_CA0B25C4A8F6__INCLUDED_)
