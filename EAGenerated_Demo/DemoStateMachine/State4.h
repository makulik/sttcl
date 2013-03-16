///////////////////////////////////////////////////////////
//  State4.h
//  Implementation of the Class State4
//  Created on:      17-Jul-2012 22:48:12
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_7B8A3C3A_6693_4998_B935_F1F3C8BA1566__INCLUDED_)
#define EA_7B8A3C3A_6693_4998_B935_F1F3C8BA1566__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "RegionA.h"

// Forward declarations from state diagram (SttclState)
class State4
: public sttcl::State<State4,RegionA,State3_IInnerEvents >
{

public:
	typedef sttcl::State<State4,RegionA,State3_IInnerEvents > StateBaseClass;

	virtual ~State4();
	static State4& getInstance();
	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);

private:
	State4();

};
#endif // !defined(EA_7B8A3C3A_6693_4998_B935_F1F3C8BA1566__INCLUDED_)
