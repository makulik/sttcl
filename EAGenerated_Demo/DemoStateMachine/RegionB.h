///////////////////////////////////////////////////////////
//  RegionB.h
//  Implementation of the Class RegionB
//  Created on:      17-Jul-2012 22:48:04
//  Original author: Admin
///////////////////////////////////////////////////////////

#if !defined(EA_1064C140_52E8_417c_A648_6E41EB033CDA__INCLUDED_)
#define EA_1064C140_52E8_417c_A648_6E41EB033CDA__INCLUDED_

// EA generated imports
#include <Region.h>
// Sttcl generated imports
#include "State3.h"
#include "DemoStateMachine.h"

// Forward declarations from state diagram (SttclRegion)

class RegionB
: public sttcl::Region<RegionB,State3,State3_IInnerEvents,State3_DispatchEventArgsBase,sttcl::CompositeStateHistoryType::Shallow>
{

public:
	typedef sttcl::Region<RegionB,State3,State3_IInnerEvents,State3_DispatchEventArgsBase,sttcl::CompositeStateHistoryType::Shallow> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	RegionB(State3* regionContainer);
	virtual ~RegionB();
	RegionB::InnerStateClass* getInitialStateImpl() const;
	virtual void handleEvent1(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent2(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent3(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);
	virtual void handleEvent4(State3* context, State3_IInnerEvents::RegionContext* regionContext, sttcl::RefCountPtr<State3_DispatchEventArgsBase>& eventArgs);

};
#endif // !defined(EA_1064C140_52E8_417c_A648_6E41EB033CDA__INCLUDED_)
