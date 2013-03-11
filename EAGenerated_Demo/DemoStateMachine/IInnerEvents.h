///////////////////////////////////////////////////////////
//  IInnerEvents.h
//  Implementation of the Interface IInnerEvents
//  Created on:      17-Jul-2012 22:48:02
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_D7FF6DB6_140D_4206_A5EB_8D4DDD0487F0__INCLUDED_)
#define EA_D7FF6DB6_140D_4206_A5EB_8D4DDD0487F0__INCLUDED_

#include <string>
#include <vector>

// EA generated imports
// Sttcl generated imports

// Forward declarations from state diagram (SttclStateInterface)
class DemoStateMachine;

class IInnerEvents
{

public:
	virtual ~IInnerEvents() {

	}

	virtual void handleEvent1(DemoStateMachine* context, int p1, std::string& p2) =0;
	virtual void handleEvent2(DemoStateMachine* context, double p1, double p2) =0;
	virtual void handleEvent3(DemoStateMachine* context) =0;
	virtual void handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3) =0;

};
#endif // !defined(EA_D7FF6DB6_140D_4206_A5EB_8D4DDD0487F0__INCLUDED_)
