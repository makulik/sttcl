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

#endif /* STTCLCONFIG_H_ */
