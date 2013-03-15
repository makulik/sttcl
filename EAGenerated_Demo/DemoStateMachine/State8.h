///////////////////////////////////////////////////////////
//  State8.h
//  Implementation of the Class State8
//  Created on:      17-Jul-2012 22:48:17
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_5985F0B0_758B_4c44_A34B_52C5AF09B4FE__INCLUDED_)
#define EA_5985F0B0_758B_4c44_A34B_52C5AF09B4FE__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "RegionB.h"

// Forward declarations from state diagram (SttclState)
class State8
: public sttcl::State<State8,RegionB,State3_IInnerEvents >
{

public:
	typedef sttcl::State<State8,RegionB,State3_IInnerEvents > StateBaseClass;

	virtual ~State8();
	static State8& getInstance();
	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);

private:
	State8();

};
#endif // !defined(EA_5985F0B0_758B_4c44_A34B_52C5AF09B4FE__INCLUDED_)
