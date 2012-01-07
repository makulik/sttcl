/*
 * DemoState3b.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3B_H_
#define DEMOSTATE3B_H_

#include "DemoState3.h"
#include "CompositeState.h"
#include "IDemoState3b.h"

namespace Application
{

class DemoState3b
: public sttcl::CompositeState<DemoState3b,DemoState3,IDemoState3b,sttcl::CompositeStateHistoryType::Shallow>
{
public:
	typedef typename sttcl::CompositeState<DemoState3b,DemoState3,IDemoState3b,sttcl::CompositeStateHistoryType::Shallow>::StateBaseClass InnerStateBaseClass;
	typedef sttcl::CompositeState<DemoState3b,DemoState3,IDemoState3b,sttcl::CompositeStateHistoryType::Shallow> StateBaseClass;

	DemoState3b(DemoState3* context);
	virtual ~DemoState3b();

	virtual void handleEvent1(DemoState3* context);
	virtual void handleEvent2(DemoState3* context);
	virtual void handleEvent3(DemoState3* context);
	virtual void handleEvent4(DemoState3* context);
	virtual void handleEvent5(DemoState3* context);

    bool initializeImpl(bool force);
    void finalizeImpl(bool finalizeSubStateMachines);

	void entryImpl(DemoState3* context);
	void exitImpl(DemoState3* context);

	InnerStateBaseClass* getInitialStateImpl() const;

	inline DemoState3* getContext() const
	{
		return demoState3;
	}

	int getX() const;
	int getY() const;
	int getZ() const;

private:
	DemoState3* demoState3;

};

}

#endif /* DEMOSTATE3B_H_ */
