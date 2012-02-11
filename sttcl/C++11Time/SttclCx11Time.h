/*
 * SttclCx11Time.h
 *
 *  Created on: 29.12.2011
 *      Author: Admin
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
