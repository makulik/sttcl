/*
 * IDemo3aEventHandler.h
 *
 *  Created on: Jul 1, 2013
 *      Author: user
 */

#ifndef IDEMO3AEVENTHANDLER_H_
#define IDEMO3AEVENTHANDLER_H_

namespace Demo3a
{

    template<typename ContextClass>
    struct IDemo3aEventHandler
    {
        virtual void handleEvent1(ContextClass* context) = 0;
        virtual void handleEvent2(ContextClass* context) = 0;
        virtual void handleEvent3(ContextClass* context) = 0;
        virtual void handleEvent4(ContextClass* context) = 0;
        virtual void handleEvent5(ContextClass* context) = 0;

        virtual ~IDemo3aEventHandler() {}
    };
}


#endif /* IDEMO3AEVENTHANDLER_H_ */
