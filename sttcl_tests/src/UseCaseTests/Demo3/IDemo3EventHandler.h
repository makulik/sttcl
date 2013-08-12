/*
 * IDemo3EventHandler.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef IDEMO3EVENTHANDLER_H_
#define IDEMO3EVENTHANDLER_H_

namespace Demo3
{

    template<typename ContextClass>
    struct IDemo3EventHandler
    {
        virtual void handleEvent1(ContextClass* context) = 0;
        virtual void handleEvent2(ContextClass* context) = 0;
        virtual void handleEvent3(ContextClass* context) = 0;
        virtual void handleEvent4(ContextClass* context) = 0;
        virtual void handleEvent5(ContextClass* context) = 0;

        virtual ~IDemo3EventHandler() {}
    };
}


#endif /* IDEMO3EVENTHANDLER_H_ */
