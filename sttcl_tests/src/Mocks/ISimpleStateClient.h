/*
 * ISimpleStateClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ISIMPLESTATECLIENT_H_
#define ISIMPLESTATECLIENT_H_

template
    < typename ContextType
    , typename StateBaseType
    >
struct ISimpleStateClient
{
    typedef ContextType Context;

    virtual void entryImpl(Context* context) = 0;
    virtual void exitImpl(Context* context) = 0;
    virtual void startDoImpl(Context* context) = 0;
    virtual void endDoImpl(Context* context) = 0;
    virtual void joinDoActionImpl(Context* context) = 0;
    virtual void finalizeSubStateMachinesImpl(bool recursive) = 0;
    virtual void initSubStateMachinesImpl(bool recursive) = 0;
    virtual bool checkDirectTransitionImpl(Context* context, bool& finalize, StateBaseType*& nextState) = 0;

    virtual ~ISimpleStateClient() {}
};


#endif /* ISIMPLESTATECLIENT_H_ */
