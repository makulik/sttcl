/*
 * IDemoState3.h
 *
 *  Created on: 12.12.2011
 *      Author: Admin
 */

#ifndef IDEMOSTATE3_H_
#define IDEMOSTATE3_H_

namespace Application
{

class DemoState3;

class IDemoState3
{
public:
	virtual void handleEvent1(DemoState3* context) = 0;
	virtual void handleEvent2(DemoState3* context) = 0;
	virtual void handleEvent3(DemoState3* context) = 0;
	virtual void handleEvent4(DemoState3* context) = 0;
	virtual void handleEvent5(DemoState3* context) = 0;
	virtual ~IDemoState3() {}
};

}

#endif /* IDEMOSTATE3_H_ */
