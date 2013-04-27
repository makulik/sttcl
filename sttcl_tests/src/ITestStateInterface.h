/*
 * ITestStateInterface.h
 *
 *  Created on: Apr 15, 2013
 *      Author: user
 */

#ifndef ITESTSTATEINTERFACE_H_
#define ITESTSTATEINTERFACE_H_

class SttclStateMachineMock;

class ITestStateInterface
{
public:
    typedef SttclStateMachineMock Context;

	virtual void handleEvent1(SttclStateMachineMock* context) = 0;
	virtual void handleEvent2(SttclStateMachineMock* context) = 0;
	virtual void handleEvent3(SttclStateMachineMock* context) = 0;
	virtual void handleEvent4(SttclStateMachineMock* context) = 0;

	virtual ~ITestStateInterface() {}
};


#endif /* ITESTSTATEINTERFACE_H_ */
