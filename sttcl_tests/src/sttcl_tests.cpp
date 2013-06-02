//============================================================================
// Name        : sttcl_tests.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SttclTestLog.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::FLAGS_gmock_verbose = "error";

	SttclTestLogManager::instance().logFilename("sttcl_tests_debug.log");
	SttclTestLogManager::logLevelEnabled(SttclTestLogLevel::All);

	return RUN_ALL_TESTS();
}
