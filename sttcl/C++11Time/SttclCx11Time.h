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

#ifndef STTCLCX11TIME_H_
#define STTCLCX11TIME_H_

#include <chrono>

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
	typedef std::chrono::nanoseconds NativeTimeDuration;

	SttclCx11TimeDuration(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: td(std::chrono::hours(argHours) +
		 std::chrono::minutes(argMinutes) +
		 std::chrono::seconds(argSeconds))
	{
		td += std::chrono::milliseconds(argMilliSeconds);
		td += std::chrono::microseconds(argMicroSeconds);
		td += std::chrono::nanoseconds(argNanoSeconds);
	}
	SttclCx11TimeDuration(const SttclCx11TimeDuration& rhs)
	: td(rhs.td)
	{
	}
	SttclCx11TimeDuration(const NativeTimeDuration& nativeTimeDuration)
	: td(nativeTimeDuration)
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


//	long hours() const
//	{
//		return td.hours();
//	}
//
//	long minutes() const
//	{
//		return td.minutes();
//	}
//
//	long seconds() const
//	{
//		return td.seconds();
//	}
//	long milliseconds() const
//	{
//		return td.total_milliseconds();
//	}
//	long microseconds() const
//	{
//		return td.total_microseconds();
//	}
//	long nanoseconds() const
//	{
//		return td.total_nanoseconds();
//	}
//
//	void hours(int newHours)
//	{
//		NativeTimeDuration result(td);
//		result -= NativeTimeDuration(td.hours() + newHours,0,0);
//		td = result;
//	}
//	void minutes(int newMinutes)
//	{
//		NativeTimeDuration result(td);
//		result -= NativeTimeDuration(0,td.minutes() + newMinutes,0);
//		td = result;
//	}
//	void seconds(int newSeconds)
//	{
//		NativeTimeDuration result(td);
//		result -= NativeTimeDuration(0,0,td.seconds() + newSeconds);
//		td = result;
//	}
	/*
	void milliseconds(int newMilliSeconds)
	{
		NativeTimeDuration result(td);
		result -= std::time::milliseconds(td.total_milliseconds());
		result += std::time::milliseconds(newMilliSeconds);
		td = result;
	}
	void microseconds(int newMicroSeconds)
	{
		NativeTimeDuration result(td);
		result -= std::time::microseconds(td.total_microseconds());
		result += std::time::microseconds(newMicroSeconds);
		td = result;
	}
	void nanoseconds(long newNanoSeconds)
	{
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS

		NativeTimeDuration result(td);
		result -= std::time::nanoseconds(td.total_nanoseconds());
		result += std::time::nanoseconds(newNanoSeconds);
		td = result;
#endif
	}
	*/
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
