/*
 * ICompositeStateClient.h
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
struct ICompositeStateClient
: public ISimpleStateClient<ContextType,StateBaseType>
{
    typedef ContextType Context;


    virtual ~ICompositeStateClient() {}
};


#endif /* IACTIVESTATECLIENT_H_ */
