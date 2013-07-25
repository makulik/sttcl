/*
 * SttclTestMockBaseClass.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef STTCLTESTMOCKBASECLASS_H_
#define STTCLTESTMOCKBASECLASS_H_

class SttclTestMockBaseClass
{
public:
    virtual ~SttclTestMockBaseClass() {}

    const std::string& id() const { return id_; }

    bool loggingEnabled() const { return loggingEnabled_; }
    void enableLogging(bool value) { loggingEnabled_ = value; }


protected:
    SttclTestMockBaseClass(const std::string& id = "<anonymous>", bool loggingEnabled = false)
    : id_(id)
    , loggingEnabled_(loggingEnabled)
    {
    }

    SttclTestMockBaseClass(const SttclTestMockBaseClass& rhs)
    : id_(rhs.id_)
    , loggingEnabled_(rhs.loggingEnabled_)
    {
    }

    std::string id_;
    bool loggingEnabled_;
};

#endif /* STTCLTESTMOCKBASECLASS_H_ */
