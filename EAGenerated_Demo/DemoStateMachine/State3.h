///////////////////////////////////////////////////////////
//  State3.h
//  Implementation of the Class State3
//  Created on:      17-Jul-2012 22:48:08
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_F7824BB9_14B9_45cc_8C61_CC6B39352D17__INCLUDED_)
#define EA_F7824BB9_14B9_45cc_8C61_CC6B39352D17__INCLUDED_

// EA generated imports
#include <ConcurrentCompositeState.h>
#include <State.h>
#include "State3_DispatchEventArgsBase.h"
// Sttcl generated imports
#include "DemoStateMachine.h"
#include "State3_IInnerEvents.h"

// Forward declarations from state diagram (SttclConcurrentCompositeState)
class RegionA;
class RegionB;

class State3
: public sttcl::ConcurrentCompositeState<State3,DemoStateMachine,State3_IInnerEvents,2,State3_DispatchEventArgsBase>
{

public:
	typedef sttcl::StateBase<State3,State3_IInnerEvents> InnerStateBaseClass;

	typedef sttcl::ConcurrentCompositeState<State3,DemoStateMachine,State3_IInnerEvents,2,State3_DispatchEventArgsBase> CompositeStateBase;

	struct Event1Args
	: public State3_DispatchEventArgsBase
	{

	public:
		int p1;
		std::string p2;

		Event1Args();
		virtual ~Event1Args();

	};

	struct Event2Args
	: public State3_DispatchEventArgsBase
	{

	public:
		double p1;
		double p2;

		Event2Args();
		virtual ~Event2Args();

	};

	struct Event3Args
	: public State3_DispatchEventArgsBase
	{

	public:
		Event3Args();
		virtual ~Event3Args();

	};

	struct Event4Args
	: public State3_DispatchEventArgsBase
	{

	public:
		int p1;
		long p2;
		std::vector<int> p3;

		Event4Args();
		virtual ~Event4Args();

	};

	State3(DemoStateMachine* context);
	virtual ~State3();
	bool checkDirectTransitionImpl(DemoStateMachine* context, bool& finalize, sttcl::StateBase<DemoStateMachine,IInnerEvents>*& nextState);
	virtual void handleEvent1(DemoStateMachine* context, int p1, std::string& p2);
	virtual void handleEvent2(DemoStateMachine* context, double p1, double p2);
	virtual void handleEvent3(DemoStateMachine* context);
	virtual void handleEvent4(DemoStateMachine* context, int p1, long p2, std::vector<int>& p3);
private:
	RegionA* regionA;
	RegionB* regionB;
	CompositeStateBase::RegionsArray regions;

};
#endif // !defined(EA_F7824BB9_14B9_45cc_8C61_CC6B39352D17__INCLUDED_)
