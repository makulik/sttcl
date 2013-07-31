/*
 * IDemoState3InnerState.h
 *
 *  Created on: Jul 6, 2013
 *      Author: user
 */

#ifndef DEMO3A_IDEMOSTATE3INNERSTATE_H_
#define DEMO3A_IDEMOSTATE3INNERSTATE_H_

namespace Demo3a
{

struct IDemoState3InnerState
{
    virtual void handleEvent1(DemoState3* context) = 0;
    virtual void handleEvent2(DemoState3* context) = 0;
    virtual void handleEvent3(DemoState3* context) = 0;
    virtual void handleEvent4(DemoState3* context) = 0;
    virtual void handleEvent5(DemoState3* context) = 0;

    virtual ~IDemoState3InnerState() {}
};
}
#endif /* DEMO3A_IDEMOSTATE3INNERSTATE_H_ */
