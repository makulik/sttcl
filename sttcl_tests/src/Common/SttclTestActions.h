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

#define TRIGGER_STATE_CHANGE(__stateType__, __eventHandler__, __state__, __newState__ ) \
    DoAll ( Invoke(__state__, & __stateType__ :: __eventHandler__ ## Call) \
          , DoStateChange(__state__,__newState__) )
#endif /* STTCLTESTACTIONS_H_ */
