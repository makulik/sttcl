/*
 * IDemoState3b.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef IDEMOSTATE3B_H_
#define IDEMOSTATE3B_H_

namespace Application
{

class DemoState3b;

class IDemoState3b
{
public:
	virtual void handleEvent1(DemoState3b* context) = 0;
	virtual void handleEvent2(DemoState3b* context) = 0;
	virtual void handleEvent3(DemoState3b* context) = 0;
	virtual void handleEvent4(DemoState3b* context) = 0;
	virtual void handleEvent5(DemoState3b* context) = 0;
	virtual ~IDemoState3b() {}
};

}

#endif /* IDEMOSTATE3B_H_ */
