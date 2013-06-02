/*
 * IConcurrentCompositeStateClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ICONCURRENTCOMPOSITESTATECLIENT_H_
#define ICONCURRENTCOMPOSITESTATECLIENT_H_

#include "ISimpleStateClient.h"

template
    < typename ContextType
    , typename StateBaseType
    , typename RegionBaseType
    , typename InnerStateBaseType
    >
struct IConcurrentCompositeStateClient
: public ISimpleStateClient<ContextType,StateBaseType>
{
    typedef ContextType Context;

    //virtual bool isReadyImpl() const = 0;
    virtual bool initializeImpl(bool recursive) = 0;
    virtual void finalizeImpl(bool recursive) = 0;
    virtual void regionCompletedImpl(RegionBaseType* region) = 0;

    virtual ~IConcurrentCompositeStateClient() {}
};


#endif /* ICONCURRENTCOMPOSITESTATECLIENT_H_ */
