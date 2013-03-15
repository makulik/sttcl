///////////////////////////////////////////////////////////
//  State3_IInnerEvents.h
//  Implementation of the Interface State3_IInnerEvents
//  Created on:      17-Jul-2012 22:48:11
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_632120C0_2F88_47f5_BC87_C51C6072C4F2__INCLUDED_)
#define EA_632120C0_2F88_47f5_BC87_C51C6072C4F2__INCLUDED_

#include <Region.h>
// Sttcl generated imports
#include "DemoStateMachine.h"
#include "State3_DispatchEventArgsBase.h"
// Forward declarations from state diagram (SttclDispatchInterface)
class State3;

class State3_IInnerEvents
{

public:
	typedef sttcl::RegionBase<State3,State3_IInnerEvents,State3_DispatchEventArgsBase> RegionContext;


	virtual ~State3_IInnerEvents() {

	}

	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs) =0;
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs) =0;
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs) =0;
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs) =0;

};
#endif // !defined(EA_632120C0_2F88_47f5_BC87_C51C6072C4F2__INCLUDED_)
