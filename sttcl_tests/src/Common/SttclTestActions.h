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

#endif /* STTCLTESTACTIONS_H_ */
