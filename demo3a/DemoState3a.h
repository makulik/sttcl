/*
 * DemoState3a.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3A_H_
#define DEMOSTATE3A_H_

#include "IDemoState3.h"
#include "State.h"

namespace Application
{

class DemoState3a
: public sttcl::State<DemoState3a,DemoState3,IDemoState3>
{
public:
	typedef sttcl::State<DemoState3a,DemoState3,IDemoState3> StateBaseClass;

	DemoState3a();
	virtual ~DemoState3a();

	virtual void handleEvent1(DemoState3* context);
	virtual void handleEvent2(DemoState3* context);
	virtual void handleEvent3(DemoState3* context);
	virtual void handleEvent4(DemoState3* context);
	virtual void handleEvent5(DemoState3* context);

	void entryImpl(DemoState3* context);
	void exitImpl(DemoState3* context);

	static DemoState3a& getInstance();

private:

};

}

#endif /* DEMOSTATE3A_H_ */
