/*
 * RegionA.h
 *
 *  Created on: 31.12.2011
 *      Author: Admin
 */

#ifndef REGIONA_H_
#define REGIONA_H_

#include "Region.h"
#include "IConcurrentStatemachine.h"
#include "DemoStateMachine.h"

namespace Application
{

class DemoStateMachine;
class RegionA
: public sttcl::Region<RegionA,DemoStateMachine,IConcurrentStateMachine>
{
public:
	typedef sttcl::Region<RegionA,DemoStateMachine,IConcurrentStateMachine> RegionBaseClass;
	typedef typename RegionBaseClass::InnerStateClass InnerStateClass;

	RegionA();
	virtual ~RegionA();

	virtual void handleEvent1(DemoStateMachine* context,const void* eventArgs = 0);
	virtual void handleEvent2(DemoStateMachine* context,const void* eventArgs = 0);
	virtual void handleEvent3(DemoStateMachine* context,const void* eventArgs = 0);
	virtual void handleEvent4(DemoStateMachine* context,const void* eventArgs = 0);

	void entryImpl(DemoStateMachine* context);
	void exitImpl(DemoStateMachine* context);

	void startingRegionThread();
	void endingRegionThread();

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	InnerStateClass* getInitialStateImpl() const;
};

}

#endif /* REGIONA_H_ */
