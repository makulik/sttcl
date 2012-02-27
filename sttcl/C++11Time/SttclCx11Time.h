/**
 * @file SttclCx11Time.h
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

#ifndef STTCLCX11TIME_H_
#define STTCLCX11TIME_H_

#if defined(STTCL_CX11_TIME) or defined(STTCL_CX11_IMPL)
namespace sttcl
{

namespace internal
{
namespace cx11_impl
{
/**
 * The C++ 11 standard default implementation for sttcl::TimeDuration<>.
 */
class SttclCx11TimeDuration
{
public:
	typedef boost::posix_time::time_duration NativeTimeDuration;

	SttclCx11TimeDuration(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: td(argHours,argMinutes,argSeconds,NativeTimeDuration::fractional_seconds_type(0))
	{
		td += boost::posix_time::milliseconds(argMilliSeconds);
		td += boost::posix_time::microseconds(argMicroSeconds);
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		td += boost::posix_time::nanoseconds(argNanoSeconds);
#endif
	}
	SttclCx11TimeDuration(const SttclCx11TimeDuration& rhs)
	: td(rhs.td)
	{
	}
	~SttclCx11TimeDuration()
	{
	}

	SttclCx11TimeDuration& operator=(const SttclCx11TimeDuration& rhs)
	{
		td = rhs.td;
		return *this;
	}

	bool operator==(const SttclCx11TimeDuration& rhs) const
	{
		return td == rhs.td;
	}
	bool operator!=(const SttclCx11TimeDuration& rhs) const
	{
		return td != rhs.td;
	}
	bool operator<(const SttclCx11TimeDuration& rhs) const
	{
		return td < rhs.td;
	}
	bool operator<=(const SttclCx11TimeDuration& rhs) const
	{
		return td <= rhs.td;
	}

	bool operator>(const SttclCx11TimeDuration& rhs) const
	{
		return td > rhs.td;
	}
	bool operator>=(const SttclCx11TimeDuration& rhs) const
	{
		return td >= rhs.td;
	}

	SttclCx11TimeDuration& operator+=(const SttclCx11TimeDuration& rhs)
	{
		td += rhs.td;
		return *this;
	}

	SttclCx11TimeDuration& operator-=(const SttclCx11TimeDuration& rhs)
	{
		td -= rhs.td;
		return *this;
	}

	SttclCx11TimeDuration& operator*=(int factor)
	{
		td *=factor;
		return *this;
	}

	SttclCx11TimeDuration& operator/=(int divider)
	{
		td /= divider;
		return *this;
	}


	int hours() const
	{
		return td.hours();
	}

	int minutes() const
	{
		return td.minutes();
	}

	int seconds() const
	{
		return td.seconds();
	}
	int milliseconds() const
	{
		return td.total_milliseconds();
	}
	int microseconds() const
	{
		return td.total_microseconds();
	}
	int nanoseconds() const
	{
		return td.total_nanoseconds();
	}

	void hours(int newHours)
	{
		NativeTimeDuration result(td);
		result -= NativeTimeDuration(td.hours() + newHours,0,0);
		td = result;
	}
	void minutes(int newMinutes)
	{
		NativeTimeDuration result(td);
		result -= NativeTimeDuration(0,td.minutes() + newMinutes,0);
		td = result;
	}
	void seconds(int newSeconds)
	{
		NativeTimeDuration result(td);
		result -= NativeTimeDuration(0,0,td.seconds() + newSeconds);
		td = result;
	}
	void milliseconds(int newMilliSeconds)
	{
		NativeTimeDuration result(td);
		result -= boost::posix_time::milliseconds(td.total_milliseconds());
		result += boost::posix_time::milliseconds(newMilliSeconds);
		td = result;
	}
	void microseconds(int newMicroSeconds)
	{
		NativeTimeDuration result(td);
		result -= boost::posix_time::microseconds(td.total_microseconds());
		result += boost::posix_time::microseconds(newMicroSeconds);
		td = result;
	}
	void nanoseconds(int newNanoSeconds)
	{
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS

		NativeTimeDuration result(td);
		result -= boost::posix_time::nanoseconds(td.total_nanoseconds());
		result += boost::posix_time::nanoseconds(newNanoSeconds);
		td = result;
#endif
	}

	const NativeTimeDuration& getNativeValue() const
	{
		return td;
	}

private:
	NativeTimeDuration td;
};
}
}
}
#endif
#endif /* STTCLCX11TIME_H_ */
