///////////////////////////////////////////////////////////
//  State7.h
//  Implementation of the Class State7
//  Created on:      17-Jul-2012 22:48:16
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_B9FE1222_DDD3_4818_9ED3_B9095768929B__INCLUDED_)
#define EA_B9FE1222_DDD3_4818_9ED3_B9095768929B__INCLUDED_

// EA generated imports
#include <State.h>
// Sttcl generated imports
#include "RegionB.h"

// Forward declarations from state diagram (SttclState)
class State7
: public sttcl::State<State7,RegionB,State3_IInnerEvents >
{

public:
	typedef sttcl::State<State7,RegionB,State3_IInnerEvents > StateBaseClass;

	virtual ~State7();
	static State7& getInstance();
	virtual void handleEvent1(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent2(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent3(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent4(State3* context, RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);

private:
	State7();

};
#endif // !defined(EA_B9FE1222_DDD3_4818_9ED3_B9095768929B__INCLUDED_)
