/*
 * SttclTestActions.h
 *
 *  Created on: May 12, 2013
 *      Author: user
 */

#ifndef STTCLTESTACTIONS_H_
#define STTCLTESTACTIONS_H_

#include <gmock/gmock.h>


ACTION_P2(DoStateChange,state,newState)
{
    state->doStateChange(arg0,newState);
}

ACTION_P2(DoStateChange2,state,newState)
{
    state->doStateChange(arg0,arg1,newState);
}

#define TRIGGER_STATE_CHANGE(__stateType__, __eventHandler__, __state__, __newState__ ) \
    DoAll ( Invoke(__state__, & __stateType__ :: __eventHandler__ ## Call) \
          , DoStateChange(__state__,__newState__) )

#define TRIGGER_STATE_CHANGE2(__stateType__, __eventHandler__, __state__, __newState__ ) \
    DoAll ( Invoke(__state__, & __stateType__ :: __eventHandler__ ## Call) \
          , DoStateChange2(__state__,__newState__) )

#endif /* STTCLTESTACTIONS_H_ */
