/**
 * @file SttclPosixTime.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STTCLPOSIXTIME_H_
#define STTCLPOSIXTIME_H_
#if defined(STTCL_POSIX_TIME) or defined(STTCL_POSIX_IMPL)

#include <time.h>

namespace sttcl
{

namespace internal
{
namespace posix_impl
{

/**
 * The POSIX default implementation for sttcl::TimeDuration<>.
 */
class SttclPosixTimeDuration
{
public:
	typedef struct timespec NativeTimeDuration;

	SttclPosixTimeDuration(unsigned int argHours = 0, unsigned int argMinutes = 0, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	{
		setNative(argHours,argMinutes,argSeconds,argMilliSeconds,argMicroSeconds,argNanoSeconds);
	}
	SttclPosixTimeDuration(const SttclPosixTimeDuration& rhs)
	{
		td.tv_sec = rhs.td.tv_sec;
		td.tv_nsec = rhs.td.tv_nsec;
	}
	SttclPosixTimeDuration(const NativeTimeDuration& nativeTimeDuration)
	{
		td.tv_sec = nativeTimeDuration.tv_sec;
		td.tv_nsec = nativeTimeDuration.tv_nsec;
	}
	~SttclPosixTimeDuration()
	{
	}

	SttclPosixTimeDuration& operator=(const SttclPosixTimeDuration& rhs)
	{
		td.tv_sec = rhs.td.tv_sec;
		td.tv_nsec = rhs.td.tv_nsec;
		return *this;
	}

	bool operator==(const SttclPosixTimeDuration& rhs) const
	{
		return td.tv_sec == rhs.td.tv_sec &&
			   td.tv_nsec == rhs.td.tv_nsec;
	}

	bool operator!=(const SttclPosixTimeDuration& rhs) const
	{
		return !operator==(rhs);
	}

	bool operator<(const SttclPosixTimeDuration& rhs) const
	{
		return td.tv_sec < rhs.td.tv_sec ||
			   (td.tv_sec == rhs.td.tv_sec &&
			    td.tv_nsec < rhs.td.tv_nsec);
	}

	bool operator<=(const SttclPosixTimeDuration& rhs) const
	{
		return operator==(rhs) || operator<(rhs);
	}

	bool operator>(const SttclPosixTimeDuration& rhs) const
	{
		return td.tv_sec > rhs.td.tv_sec ||
			   (td.tv_sec == rhs.td.tv_sec &&
			    td.tv_nsec > rhs.td.tv_nsec);
	}
	bool operator>=(const SttclPosixTimeDuration& rhs) const
	{
		return operator==(rhs) || operator>(rhs);
	}

	SttclPosixTimeDuration& operator+=(const SttclPosixTimeDuration& rhs)
	{
		add(rhs.td);
		return *this;
	}

	SttclPosixTimeDuration& operator-=(const SttclPosixTimeDuration& rhs)
	{
		substract(rhs.td);
		return *this;
	}

	SttclPosixTimeDuration& operator*=(int factor)
	{
		multiply(factor);
		return *this;
	}

	SttclPosixTimeDuration& operator/=(int divider)
	{
		divide(divider);
		return *this;
	}


	long hours() const
	{
		return td.tv_sec / 3600;
	}

	long minutes() const
	{
		return td.tv_sec / 60;
	}

	long seconds() const
	{
		return td.tv_sec;
	}
	long milliseconds() const
	{
		return total_milliseconds();
	}
	long microseconds() const
	{
		return total_microseconds();
	}
	long nanoseconds() const
	{
		return total_nanoseconds();
	}

	void hours(int newHours)
	{
		SttclPosixTimeDuration result(*this);
		result -= SttclPosixTimeDuration(hours() + newHours);
		*this = result;
	}
	void minutes(int newMinutes)
	{
		SttclPosixTimeDuration result(*this);
		result -= SttclPosixTimeDuration(0,minutes() + newMinutes);
		*this = result;
	}
	void seconds(int newSeconds)
	{
		SttclPosixTimeDuration result(*this);
		result -= SttclPosixTimeDuration(0,0,seconds() + newSeconds);
		*this = result;
	}
	/*
	void milliseconds(int newMilliSeconds)
	{
	}
	void microseconds(int newMicroSeconds)
	{
	}
	void nanoseconds(long newNanoSeconds)
	{
	}
	*/

	const NativeTimeDuration& getNativeValue() const
	{
		return td;
	}

private:
	void setNative(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds, unsigned int argMilliSeconds, unsigned long argMicroSeconds, unsigned long argNanoSeconds);
	void add(const NativeTimeDuration& nativeTimeDuration);
	void substract(const NativeTimeDuration& nativeTimeDuration);
	void multiply(int factor);
	void divide(int divider);
	void normalizeNative();
	inline long total_milliseconds() const
	{
		return td.tv_sec * 1000 + td.tv_nsec / 1000000;
	}
	inline long total_microseconds() const
	{
		return td.tv_sec * 1000000 + td.tv_nsec / 1000;
	}
	inline long total_nanoseconds() const
	{
		return td.tv_sec * 1000000 + td.tv_nsec / 1000;
	}

	NativeTimeDuration td;

};
}
}
}
#endif
#endif /* STTCLPOSIXTIME_H_ */
