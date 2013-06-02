/*
 * ICompositeStateClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ICOMPOSiTESTATECLIENT_H_
#define ICOMPOSiTESTATECLIENT_H_

#include "ISimpleStateClient.h"

template
    < typename ContextType
    , typename StateBaseType
    , typename InnerStateBaseType
    >
struct ICompositeStateClient
: public ISimpleStateClient<ContextType,StateBaseType>
{
    typedef ContextType Context;

    virtual bool isReadyImpl() const = 0;
    virtual bool initializeImpl(bool force) = 0;
    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;
    virtual void subStateMachineCompletedImpl(InnerStateBaseType* state) = 0;
    virtual InnerStateBaseType* getInitialStateImpl() const = 0;

    virtual ~ICompositeStateClient() {}
};


#endif /* ICOMPOSiTESTATECLIENT_H_ */
