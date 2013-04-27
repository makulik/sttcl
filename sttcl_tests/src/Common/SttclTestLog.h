/*
 * SttclTestLog.h
 *
 *  Created on: Apr 17, 2013
 *      Author: user
 */

#ifndef STTCLTESTLOG_H_
#define STTCLTESTLOG_H_

#include <iostream>

#if !defined(STTCL_TEST_LOGS)
#define STTCL_TEST_LOGS 1
#endif

#if STTCL_TEST_LOGS == 1
#define STTCL_TEST_LOG(pred,message) if((pred)) { std::cout << message << std::endl; }
#else
#define STTCL_TEST_LOG(pred,message)
#endif

#endif /* STTCLTESTLOG_H_ */
