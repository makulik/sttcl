///////////////////////////////////////////////////////////
//  State6.h
//  Implementation of the Class State6
//  Created on:      17-Jul-2012 22:48:14
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_8551E247_7B7C_4f13_A152_4DBD30C792E5__INCLUDED_)
#define EA_8551E247_7B7C_4f13_A152_4DBD30C792E5__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "RegionB.h"

// Forward declarations from state diagram (SttclState)
class State6
: public sttcl::State<State6,RegionB,State3_IInnerEvents >
{

public:
	typedef sttcl::State<State6,RegionB,State3_IInnerEvents > StateBaseClass;

	virtual ~State6();
	static State6& getInstance();
	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);

private:
	State6();

};
#endif // !defined(EA_8551E247_7B7C_4f13_A152_4DBD30C792E5__INCLUDED_)
