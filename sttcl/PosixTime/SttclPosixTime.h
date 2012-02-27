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
 * 3) Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products
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
#endif
#endif /* STTCLPOSIXTIME_H_ */
