/*
 * DemoState3b_3.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3B_3_H_
#define DEMOSTATE3B_3_H_

#include "IDemoState3b.h"
#include "State.h"

namespace Application
{

class DemoState3b_3
: public sttcl::State<DemoState3b_3,DemoState3b,IDemoState3b>
{
public:
	typedef sttcl::State<DemoState3b_3,DemoState3b,IDemoState3b> StateBaseClass;

	DemoState3b_3();
	virtual ~DemoState3b_3();

	virtual void handleEvent1(DemoState3b* context);
	virtual void handleEvent2(DemoState3b* context);
	virtual void handleEvent3(DemoState3b* context);
	virtual void handleEvent4(DemoState3b* context);
	virtual void handleEvent5(DemoState3b* context);

	void entryImpl(DemoState3b* context);
	void exitImpl(DemoState3b* context);

	static DemoState3b_3& getInstance();

private:

};

}

#endif /* DEMOSTATE3B_3_H_ */
