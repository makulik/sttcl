/*
 * EventArgs.h
 *
 *  Created on: May 7, 2013
 *      Author: user
 */

#ifndef EVENTARGS_H_
#define EVENTARGS_H_

#include <string>
#include <gmock/gmock.h>
#include "RefCountPtr.h"

class EventArgs
{
public:
    virtual ~EventArgs() {}

protected:
    EventArgs() {}
    EventArgs(const EventArgs& rhs) {}
    EventArgs& operator=(const EventArgs& rhs) { return *this; }
    bool operator==(const EventArgs& rhs) const { return this == &rhs; }
};

struct Event1Args
: public EventArgs
{
    int arg1_;
    std::string arg2_;

    Event1Args(int arg1, const std::string& arg2)
    : EventArgs()
    , arg1_(arg1)
    , arg2_(arg2)
    {}

    Event1Args(const Event1Args& rhs)
    : EventArgs(rhs)
    , arg1_(rhs.arg1_)
    , arg2_(rhs.arg2_)
    {}

    Event1Args& operator=(const Event1Args& rhs)
    {
        EventArgs::operator=(rhs);
        arg1_ = rhs.arg1_;
        arg2_ = rhs.arg2_;
        return *this;
    }

    bool operator==(const Event1Args& rhs) const
    {
        if(!EventArgs::operator==(rhs))
        {
            return (arg1_== rhs.arg1_) &&
                   (arg2_ == rhs.arg2_);
        }
        return true;
    }

    virtual ~Event1Args() {}
};

struct Event2Args
: public EventArgs
{
    double arg1_;

    Event2Args(double arg1)
    : EventArgs()
    , arg1_(arg1)
    {}

    Event2Args(const Event2Args& rhs)
    : EventArgs(rhs)
    , arg1_(rhs.arg1_)
    {}

    virtual ~Event2Args() {}

    Event2Args& operator=(const Event2Args& rhs)
    {
        EventArgs::operator=(rhs);
        arg1_ = rhs.arg1_;
        return *this;
    }

    bool operator==(const Event2Args& rhs) const
    {
        if(!EventArgs::operator==(rhs))
        {
            return (arg1_== rhs.arg1_);
        }
        return true;
    }
};

struct Event3Args
: public EventArgs
{
    Event3Args()
    : EventArgs()
    {}

    Event3Args(const Event3Args& rhs)
    : EventArgs(rhs)
    {}

    virtual ~Event3Args()
    {}

    Event3Args& operator=(const Event3Args& rhs)
    {
        EventArgs::operator=(rhs);
        return *this;
    }

    bool operator==(const Event3Args& rhs) const
    {
        if(!EventArgs::operator==(rhs))
        {
            return true;
        }
        return true;
    }
};

struct Event4Args
: public EventArgs
{
    int arg1_;

    Event4Args(int arg1)
    : EventArgs()
    , arg1_(arg1)
    {}

    Event4Args(const Event4Args& rhs)
    : EventArgs(rhs)
    , arg1_(rhs.arg1_)
    {}

    virtual ~Event4Args()
    {}

    Event4Args& operator=(const Event4Args& rhs)
    {
        EventArgs::operator=(rhs);
        arg1_ = rhs.arg1_;
        return *this;
    }

    bool operator==(const Event4Args& rhs) const
    {
        if(!EventArgs::operator==(rhs))
        {
            return (arg1_== rhs.arg1_);
        }
        return true;
    }
};

typedef sttcl::RefCountPtr<EventArgs> EventArgsPtr;
typedef sttcl::RefCountPtr<Event1Args> Event1ArgsPtr;
typedef sttcl::RefCountPtr<Event2Args> Event2ArgsPtr;
typedef sttcl::RefCountPtr<Event3Args> Event3ArgsPtr;
typedef sttcl::RefCountPtr<Event4Args> Event4ArgsPtr;

MATCHER_P2(EqualsEvent1Args, arg1, arg2, "")
{
    Event1Args* argsValue = dynamic_cast<Event1Args*>(arg.get());
    if(argsValue)
    {
        return *argsValue == Event1Args(arg1,arg2);
    }
    return false;
}

MATCHER_P(EqualsEvent2Args, arg1, "")
{
    Event2Args* argsValue = dynamic_cast<Event2Args*>(arg.get());
    if(argsValue)
    {
        return *argsValue == Event2Args(arg1);
    }
    return false;
}

MATCHER(EqualsEvent3Args, "")
{
    Event3Args* argsValue = dynamic_cast<Event3Args*>(arg.get());
    if(argsValue)
    {
        return *argsValue == Event3Args();
    }
    return false;
}

MATCHER_P(EqualsEvent4Args, arg1, "")
{
    Event4Args* argsValue = dynamic_cast<Event4Args*>(arg.get());
    if(argsValue)
    {
        return *argsValue == Event4Args(arg1);
    }
    return false;
}
#endif /* EVENTARGS_H_ */
