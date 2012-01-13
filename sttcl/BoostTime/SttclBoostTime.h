/*
 * SttclBoostTime.h
 *
 *  Created on: 29.12.2011
 *      Author: Admin
 */

#ifndef STTCLBOOSTTIME_H_
#define STTCLBOOSTTIME_H_

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost;
using namespace boost::posix_time;
using namespace boost::date_time;

namespace sttcl
{

namespace internal
{
namespace boost_impl
{
class SttclBoostTimeDuration
{
public:
	typedef boost::posix_time::time_duration NativeTimeDuration;

	SttclBoostTimeDuration(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: td(argHours,argMinutes,argSeconds,NativeTimeDuration::fractional_seconds_type(0))
	{
		td += boost::posix_time::milliseconds(argMilliSeconds);
		td += boost::posix_time::microseconds(argMicroSeconds);
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		td += boost::posix_time::nanoseconds(argNanoSeconds);
#endif
	}
	SttclBoostTimeDuration(const SttclBoostTimeDuration& rhs)
	: td(rhs.td)
	{
	}
	~SttclBoostTimeDuration()
	{
	}

	SttclBoostTimeDuration& operator=(const SttclBoostTimeDuration& rhs)
	{
		td = rhs.td;
		return *this;
	}

	bool operator==(const SttclBoostTimeDuration& rhs) const
	{
		return td == rhs.td;
	}
	bool operator!=(const SttclBoostTimeDuration& rhs) const
	{
		return td != rhs.td;
	}
	bool operator<(const SttclBoostTimeDuration& rhs) const
	{
		return td < rhs.td;
	}
	bool operator<=(const SttclBoostTimeDuration& rhs) const
	{
		return td <= rhs.td;
	}

	bool operator>(const SttclBoostTimeDuration& rhs) const
	{
		return td > rhs.td;
	}
	bool operator>=(const SttclBoostTimeDuration& rhs) const
	{
		return td >= rhs.td;
	}

	SttclBoostTimeDuration& operator+=(const SttclBoostTimeDuration& rhs)
	{
		td += rhs.td;
		return *this;
	}

	SttclBoostTimeDuration& operator-=(const SttclBoostTimeDuration& rhs)
	{
		td -= rhs.td;
		return *this;
	}

	SttclBoostTimeDuration& operator*=(int factor)
	{
		td *=factor;
		return *this;
	}

	SttclBoostTimeDuration& operator/=(int divider)
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
#endif /* STTCLBOOSTTIME_H_ */
