///////////////////////////////////////////////////////////
//  RegionA.h
//  Implementation of the Class RegionA
//  Created on:      17-Jul-2012 22:48:02
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_E1368E4E_D5B8_48a1_829F_A49246FC6950__INCLUDED_)
#define EA_E1368E4E_D5B8_48a1_829F_A49246FC6950__INCLUDED_

// EA generated imports
#include <Region.h>
// Sttcl generated imports
#include "State3.h"
#include "DemoStateMachine.h"

// Forward declarations from state diagram (SttclRegion)
class RegionA
: public sttcl::Region<RegionA,State3,State3_IInnerEvents,State3_DispatchEventArgsBase,sttcl::CompositeStateHistoryType::None>
{

public:
	typedef sttcl::Region<RegionA,State3,State3_IInnerEvents,State3_DispatchEventArgsBase,sttcl::CompositeStateHistoryType::None> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	RegionA(State3* regionContainer);
	virtual ~RegionA();
	RegionA::InnerStateClass* getInitialStateImpl() const;
	virtual void handleEvent1(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent2(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent3(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);
	virtual void handleEvent4(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase> eventArgs);

};
#endif // !defined(EA_E1368E4E_D5B8_48a1_829F_A49246FC6950__INCLUDED_)
