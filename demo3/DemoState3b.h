/*
 * DemoState3b.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3B_H_
#define DEMOSTATE3B_H_

#include "DemoState3.h"
#include "State.h"

namespace Application
{

class DemoState3b
: public sttcl::State<DemoState3b,DemoState3,IDemoState3>
{
public:
	typedef sttcl::State<DemoState3b,DemoState3,IDemoState3> StateBaseClass;

	DemoState3b();
	virtual ~DemoState3b();

	virtual void handleEvent1(DemoState3* context);
	virtual void handleEvent2(DemoState3* context);
	virtual void handleEvent3(DemoState3* context);
	virtual void handleEvent4(DemoState3* context);
	virtual void handleEvent5(DemoState3* context);

	void entryImpl(DemoState3* context);
	void exitImpl(DemoState3* context);

	static DemoState3b& getInstance();

private:

};

}

#endif /* DEMOSTATE3B_H_ */
