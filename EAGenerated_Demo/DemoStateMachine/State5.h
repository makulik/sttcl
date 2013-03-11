///////////////////////////////////////////////////////////
//  State5.h
//  Implementation of the Class State5
//  Created on:      17-Jul-2012 22:48:13
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_377F5265_277A_45bd_9D55_957FE5E4A8AF__INCLUDED_)
#define EA_377F5265_277A_45bd_9D55_957FE5E4A8AF__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "RegionA.h"

// Forward declarations from state diagram (SttclState)
class State5
: public sttcl::State<State5,RegionA,State3_IInnerEvents >
{

public:
	typedef sttcl::State<State5,RegionA,State3_IInnerEvents > StateBaseClass;

	virtual ~State5();
	void exitImpl(RegionA* region);
	static State5& getInstance();
	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);

private:
	State5();

};
#endif // !defined(EA_377F5265_277A_45bd_9D55_957FE5E4A8AF__INCLUDED_)
