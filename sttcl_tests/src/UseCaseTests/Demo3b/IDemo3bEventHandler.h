/*
 * IDemo3bEventHandler.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef IDEMO3BEVENTHANDLER_H_
#define IDEMO3BEVENTHANDLER_H_

namespace Demo3b
{

    template<typename ContextClass>
    struct IDemo3bEventHandler
    {
        virtual void handleEvent1(ContextClass* context) = 0;
        virtual void handleEvent2(ContextClass* context) = 0;
        virtual void handleEvent3(ContextClass* context) = 0;
        virtual void handleEvent4(ContextClass* context) = 0;
        virtual void handleEvent5(ContextClass* context) = 0;

        virtual ~IDemo3bEventHandler() {}
    };
}


#endif /* IDEMO3BSTATE_H_ */
