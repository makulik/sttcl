/*
 * SttclPosixTime.h
 *
 *  Created on: 29.12.2011
 *      Author: Admin
 */

#ifndef STTCLPOSIXTIME_H_
#define STTCLPOSIXTIME_H_


namespace sttcl
{

namespace internal
{
namespace posix_impl
{
class SttclPosixTimeDuration
{
public:
	typedef long NativeTimeDuration;

	SttclPosixTimeDuration(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	{
	}
	SttclPosixTimeDuration(const SttclPosixTimeDuration& rhs)
	{
	}
	~SttclPosixTimeDuration()
	{
	}

	SttclPosixTimeDuration& operator=(const SttclPosixTimeDuration& rhs)
	{
		return *this;
	}

	bool operator==(const SttclPosixTimeDuration& rhs) const
	{
	}
	bool operator!=(const SttclPosixTimeDuration& rhs) const
	{
	}
	bool operator<(const SttclPosixTimeDuration& rhs) const
	{
	}
	bool operator<=(const SttclPosixTimeDuration& rhs) const
	{
	}

	bool operator>(const SttclPosixTimeDuration& rhs) const
	{
	}
	bool operator>=(const SttclPosixTimeDuration& rhs) const
	{
	}

	SttclPosixTimeDuration& operator+=(const SttclPosixTimeDuration& rhs)
	{
		return *this;
	}

	SttclPosixTimeDuration& operator-=(const SttclPosixTimeDuration& rhs)
	{
		return *this;
	}

	SttclPosixTimeDuration& operator*=(int factor)
	{
		return *this;
	}

	SttclPosixTimeDuration& operator/=(int divider)
	{
		return *this;
	}


	int hours() const
	{
	}

	int minutes() const
	{
	}

	int seconds() const
	{
	}
	int milliseconds() const
	{
	}
	int microseconds() const
	{
	}
	int nanoseconds() const
	{
	}

	void hours(int newHours)
	{
	}
	void minutes(int newMinutes)
	{
	}
	void seconds(int newSeconds)
	{
	}
	void milliseconds(int newMilliSeconds)
	{
	}
	void microseconds(int newMicroSeconds)
	{
	}
	void nanoseconds(int newNanoSeconds)
	{
	}

	const NativeTimeDuration& getNativeValue() const
	{
	}

private:
};
}
}
}
#endif /* STTCLPOSIXTIME_H_ */
