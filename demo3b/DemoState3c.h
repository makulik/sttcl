/*
 * DemoState3c.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef DEMOSTATE3C_H_
#define DEMOSTATE3C_H_

#include "IDemoState3.h"
#include "State.h"

namespace Application
{

class DemoState3c
: public sttcl::State<DemoState3c,DemoState3,IDemoState3>
{
public:
	typedef sttcl::State<DemoState3c,DemoState3,IDemoState3> StateBaseClass;

	DemoState3c();
	virtual ~DemoState3c();

	virtual void handleEvent1(DemoState3* context);
	virtual void handleEvent2(DemoState3* context);
	virtual void handleEvent3(DemoState3* context);
	virtual void handleEvent4(DemoState3* context);
	virtual void handleEvent5(DemoState3* context);

	void entryImpl(DemoState3* context);
	void exitImpl(DemoState3* context);

	static DemoState3c& getInstance();

private:

};

}

#endif /* DEMOSTATE3C_H_ */
