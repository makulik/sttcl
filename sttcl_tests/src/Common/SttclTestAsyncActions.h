/*
 * SttclTestAsyncActions.h
 *
 *  Created on: May 3, 2013
 *      Author: user
 */

#ifndef STTCLTESTASYNCACTIONS_H_
#define STTCLTESTASYNCACTIONS_H_

#include <gmock/gmock.h>

// Specialize an action that synchronizes with the calling thread
ACTION_P(ReturnFromAsyncCall,SemDone)
{
    SemDone->post();
}

// Specialize an action that synchronizes with the calling thread
ACTION_P2(ReturnFromAsyncCall,RetVal,SemDone)
{
    SemDone->post();
    return RetVal;
}


#endif /* STTCLTESTASYNCACTIONS_H_ */
