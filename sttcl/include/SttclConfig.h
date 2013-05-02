/*
 * SttclConfig.h
 *
 *  Created on: 13.03.2013
 *      Author: Admin
 */

#ifndef STTCLCONFIG_H_
#define STTCLCONFIG_H_

#define STTCL_USE_STL
#define STTCL_THREADSAFE_IMPL

#define STTCL_HAVE_RTTI
#define STTCL_HAVE_HIGHRES_CLOCK

#if defined(__GXX_EXPERIMENTAL_CXX0X__)
#if defined(STTCL_HAVE_HIGHRES_CLOCK)
#define _GLIBCXX_USE_NANOSLEEP
#endif
#endif

#if defined(STTCL_POSIX_IMPL)
#if defined(STTCL_HAVE_HIGHRES_CLOCK)
#define STTCL_POSIX_NANOSLEEP
#endif
#endif

#if defined(STTCL_THREADSAFE_IMPL)
#include "SttclMutex.h"
#endif

#if defined(STTCL_THREADSAFE_IMPL) && !defined(STTCL_STATEMACHINE_SAFE_RETURN)
#define STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,_ReturnValue_) \
        sttcl::internal::AutoLocker<StateMachineMutexType> lock(internalLockGuard); \
        return (_ReturnValue_);
#else
#define STTCL_STATEMACHINE_SAFE_RETURN(internalLockGuard,_ReturnValue_)
#endif

#if defined(STTCL_THREADSAFE_IMPL) && !defined(STTCL_STATEMACHINE_SAFESECTION_START)
#define STTCL_STATEMACHINE_SAFESECTION_START(internalLockGuard) \
        { sttcl::internal::AutoLocker<StateMachineMutexType> lock(internalLockGuard);
#else
#define STTCL_STATEMACHINE_SAFESECTION_START
#endif

#if defined(STTCL_THREADSAFE_IMPL) && !defined(STTCL_STATEMACHINE_SAFESECTION_END)
#define STTCL_STATEMACHINE_SAFESECTION_END \
        }
#else
#define STTCL_STATEMACHINE_SAFESECTION_END
#endif

#endif /* STTCLCONFIG_H_ */
