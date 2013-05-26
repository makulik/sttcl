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

class SttclTestLogManager;

#if STTCL_TEST_LOGS == 1
#define STTCL_TEST_LOG(pred,logLevel,message) if((pred) && SttclTestLogManager::logLevelEnabled(logLevel)) { SttclTestLogManager::logStream(logLevel) << message << std::endl; }
#else
#define STTCL_TEST_LOG(pred,logLevel,message)
#endif

struct SttclTestLogLevel
{
    enum Values
    {
        All = 0 ,
        Error ,
        Warning ,
        Info ,
        Debug ,
        None ,
    };
};

class SttclTestLogManager
{
public:
    ~SttclTestLogManager() {}

    SttclTestLogLevel::Values currentLogLevel() const { return currentLogLevel_; }
    void currentLogLevel(SttclTestLogLevel::Values newValue) { currentLogLevel_ = newValue; }

    bool isLogLevelEnabled(SttclTestLogLevel::Values level) const
    {
        return level >= currentLogLevel_;
    }

    static SttclTestLogManager& instance()
    {
        static SttclTestLogManager theLogManager;
        return theLogManager;
    }

    static bool logLevelEnabled(SttclTestLogLevel::Values level)
    {
        return SttclTestLogManager::instance().isLogLevelEnabled(level);
    }

    static std::ostream& logStream(SttclTestLogLevel::Values level)
    {
        switch(level)
        {
        case SttclTestLogLevel::Error:
        case SttclTestLogLevel::Warning:
            return std::cerr;
        default:
            return std::cout;
        }
    }

private:
    SttclTestLogManager()
    : currentLogLevel_(SttclTestLogLevel::All)
    {
    }

    SttclTestLogLevel::Values currentLogLevel_;
};

#define STTCL_LOGDEBUG2(pred,message) STTCL_TEST_LOG(pred,SttclTestLogLevel::Debug, message)
#define STTCL_LOGDEBUG1(message) STTCL_LOGDEBUG2(true, message)
#define STTCL_MOCK_LOGDEBUG(mock_class_name,message) \
            STTCL_LOGDEBUG2( mock_class_name :: loggingEnabled() \
                , #mock_class_name << "(" << mock_class_name :: id() << "): " << \
                  message )

#define STTCL_LOGINFO2(pred,message) STTCL_TEST_LOG(pred,SttclTestLogLevel::Info, message)
#define STTCL_LOGINFO1(message) STTCL_LOGINFO2(true, message)
#define STTCL_MOCK_LOGINFO(mock_class_name,message) \
            STTCL_LOGINFO2( mock_class_name :: loggingEnabled() \
                , #mock_class_name << "(" << mock_class_name :: id() << "): " << \
                  message )

#define STTCL_LOGWARNING2(pred,message) STTCL_TEST_LOG(pred,SttclTestLogLevel::Warning, message)
#define STTCL_LOGWARNING1(message) STTCL_LOGWARNING2(true, message)
#define STTCL_MOCK_LOGWARNING(mock_class_name,message) \
            STTCL_LOGWARNING2( mock_class_name :: loggingEnabled() \
                , #mock_class_name << "(" << mock_class_name :: id() << "): " << \
                  message )

#define STTCL_LOGERROR2(pred,message) STTCL_TEST_LOG(pred,SttclTestLogLevel::Error, message)
#define STTCL_LOGERROR1(message) STTCL_LOGERROR2(true, message)
#define STTCL_MOCK_LOGERROR(mock_class_name,message) \
            STTCL_LOGERROR2( mock_class_name :: loggingEnabled() \
                , #mock_class_name << "(" << mock_class_name :: id() << "): " << \
                  message )

#endif /* STTCLTESTLOG_H_ */
