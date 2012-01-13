/*
 * SttclTime.h
 *
 *  Created on: 25.12.2011
 *      Author: Admin
 */

#ifndef STTCLTIME_H_
#define STTCLTIME_H_

#if defined(STTCL_POSIX_TIME)
#elif defined(STTCL_BOOST_TIME)
#include "../BoostTime/SttclBoostTime.h"
#define DEFAULT_TIMEDURATION_IMPL sttcl::internal::boost_impl::SttclBoostTimeDuration
#endif

namespace sttcl
{

template<class Implementation = DEFAULT_TIMEDURATION_IMPL>
class TimeDuration
: public Implementation
{
public:
	typedef typename Implementation::NativeTimeDuration NativeTimeDuration;

	static const TimeDuration<Implementation> Zero;

	TimeDuration(unsigned int argHours = 0, unsigned int argMinutes = 0, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: Implementation(argHours,argMinutes,argSeconds,argMilliSeconds,argMicroSeconds,argNanoSeconds)
	{
	}
	TimeDuration(const TimeDuration<Implementation>& rhs)
	: Implementation(static_cast<const Implementation&>(rhs))
	{
	}
	~TimeDuration()
	{
	}

	TimeDuration<Implementation>& operator=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	bool operator==(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator==(static_cast<const Implementation&>(rhs));
	}
	bool operator!=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator!=(static_cast<const Implementation&>(rhs));
	}
	bool operator<(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<(static_cast<const Implementation&>(rhs));
	}
	bool operator<=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<=(static_cast<const Implementation&>(rhs));
	}
	bool operator>(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>(static_cast<const Implementation&>(rhs));
	}
	bool operator>=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>=(static_cast<const Implementation&>(rhs));
	}

	TimeDuration<Implementation>& operator+=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator+=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	TimeDuration<Implementation>& operator-=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator-=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	TimeDuration<Implementation>& operator*=(int factor)
	{
		Implementation::operator*=(factor);
		return *this;
	}

	TimeDuration<Implementation>& operator/=(int divider)
	{
		Implementation::operator/=(divider);
		return *this;
	}

	int hours() const
	{
		return Implementation::hours();
	}
	int minutes() const
	{
		return Implementation::minutes();
	}
	int seconds() const
	{
		return Implementation::seconds();
	}
	int milliseconds() const
	{
		return Implementation::milliseconds();
	}
	int microseconds() const
	{
		return Implementation::microseconds();
	}
	int nanoseconds() const
	{
		return Implementation::nanoseconds();
	}

	void hours(int newHours)
	{
		Implementation::hours(newHours);
	}
	void minutes(int newMinutes)
	{
		Implementation::minutes(newMinutes);
	}
	void seconds(int newSeconds)
	{
		Implementation::seconds(newSeconds);
	}
	void milliseconds(int newMilliSeconds)
	{
		Implementation::milliseconds(newMilliSeconds);
	}
	void microseconds(int newMicroSeconds)
	{
		Implementation::microseconds(newMicroSeconds);
	}
	void nanoseconds(int newNanoSeconds)
	{
		Implementation::nanoseconds(newNanoSeconds);
	}

	const NativeTimeDuration& getNativeValue() const
	{
		return Implementation::getNativeValue();
	}
};


}

template<class Implementation>
static sttcl::TimeDuration<Implementation> operator+(const sttcl::TimeDuration<Implementation>& op1, const sttcl::TimeDuration<Implementation>& op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result += op2;
}

template<class Implementation>
static sttcl::TimeDuration<Implementation> operator-(const sttcl::TimeDuration<Implementation>& op1, const sttcl::TimeDuration<Implementation>& op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result -= op2;
}
template<class Implementation>
static sttcl::TimeDuration<Implementation> operator*(const sttcl::TimeDuration<Implementation>& op1, int op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result *= op2;
}
template<class Implementation>
static sttcl::TimeDuration<Implementation> operator/(const sttcl::TimeDuration<Implementation>& op1, int op2)
{
	sttcl::TimeDuration<Implementation> result(op1);
	return result /= op2;
}

template<class Implementation>
const sttcl::TimeDuration<Implementation> sttcl::TimeDuration<Implementation>::Zero = sttcl::TimeDuration<Implementation>();
#endif /* STTCLTIME_H_ */
