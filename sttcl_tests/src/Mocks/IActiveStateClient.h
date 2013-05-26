/*
 * IActiveStateClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef IACTIVESTATECLIENT_H_
#define IACTIVESTATECLIENT_H_

#include "ISimpleStateClient.h"

template
    < typename ContextType
    , typename StateBaseType
    >
struct IActiveStateClient
: public ISimpleStateClient<ContextType,StateBaseType>
{
    typedef ContextType Context;

    virtual void doActionImpl(Context* context, bool firstCall) = 0;
    virtual bool endDoActionRequestedImpl() = 0;
    virtual void exitingDoActionImpl() = 0;
    virtual void joinDoActionThreadImpl() = 0;
    virtual void unblockDoActionImpl() = 0;

    virtual ~IActiveStateClient() {}
};


#endif /* IACTIVESTATECLIENT_H_ */
