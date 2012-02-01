/*
 * SttclTime.h
 *
 *  Created on: 25.12.2011
 *      Author: Admin
 */

#ifndef STTCLTIME_H_
#define STTCLTIME_H_

#ifndef STTCL_DEFAULT_TIMEDURATION_IMPL
#if defined(STTCL_POSIX_TIME)  or defined(STTCL_POSIX_IMPL)
#elif defined(STTCL_BOOST_TIME) or defined(STTCL_BOOST_IMPL)
#include "../BoostTime/SttclBoostTime.h"
#define STTCL_DEFAULT_TIMEDURATION_IMPL sttcl::internal::boost_impl::SttclBoostTimeDuration
#endif

#ifndef STTCL_DEFAULT_TIMEDURATION_IMPL
#error "You need to define a default time duration implementation for sttcl"
#endif
#endif

namespace sttcl
{

/**
 * Adapter class for a (OS-)specific "real"-time duration representation implementation.
 * @tparam Implementation Selects a (OS-)specific "real"-time duration representation implementation.
 */
template<class Implementation = STTCL_DEFAULT_TIMEDURATION_IMPL>
class TimeDuration
: public Implementation
{
public:
	/**
	 * The class type of the native "real"-time duration representation.
	 */
	typedef typename Implementation::NativeTimeDuration NativeTimeDuration;

	/**
	 * Represents a zero time duration.
	 */
	static const TimeDuration<Implementation> Zero;

	/**
	 * Constructor for class TimeDuration.
	 * @param argHours The hours represented in this instance.
	 * @param argMinutes The minutes represented in this instance.
	 * @param argSeconds  The seconds represented in this instance.
	 * @param argMilliSeconds The milliseconds represented in this instance.
	 * @param argMicroSeconds The microseconds represented in this instance.
	 * @param argNanoSeconds The nanoseconds represented in this instance.
	 */
	TimeDuration(unsigned int argHours = 0, unsigned int argMinutes = 0, unsigned int argSeconds = 0, unsigned int argMilliSeconds = 0, unsigned long argMicroSeconds = 0, unsigned long argNanoSeconds = 0)
	: Implementation(argHours,argMinutes,argSeconds,argMilliSeconds,argMicroSeconds,argNanoSeconds)
	{
	}

	/**
	 * Copy constructor for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 */
	TimeDuration(const TimeDuration<Implementation>& rhs)
	: Implementation(static_cast<const Implementation&>(rhs))
	{
	}
	/**
	 * Destructor for class TimeDuration.
	 */
	~TimeDuration()
	{
	}

	/**
	 * Assignment operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the assigned TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration equals this instance, \c false otherwise.
	 */
	bool operator==(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator==(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Inequality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration doesn't equal this instance, \c false otherwise.
	 */
	bool operator!=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator!=(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Less comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is less than this instance, \c false otherwise.
	 */
	bool operator<(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Less or equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is less than or equals this instance, \c false otherwise.
	 */
	bool operator<=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator<=(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Greater comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is greater than this instance, \c false otherwise.
	 */
	bool operator>(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>(static_cast<const Implementation&>(rhs));
	}
	/**
	 * Greater or equality comparison operator for class TimeDuration.
	 * @param rhs Another instance of TimeDuration.
	 * @return \c true if \em rhs time duration is greater than or equals this instance, \c false otherwise.
	 */
	bool operator>=(const TimeDuration<Implementation>& rhs) const
	{
		return Implementation::operator>=(static_cast<const Implementation&>(rhs));
	}

	/**
	 * Adds the \em rhs time duration to this instance.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator+=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator+=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Substracts the \em rhs time duration from this instance.
	 * @param rhs Another instance of TimeDuration.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator-=(const TimeDuration<Implementation>& rhs)
	{
		Implementation::operator-=(static_cast<const Implementation&>(rhs));
		return *this;
	}

	/**
	 * Multiplies the \em time duration from of this instance with \em factor.
	 * @param factor The multiplication factor.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator*=(int factor)
	{
		Implementation::operator*=(factor);
		return *this;
	}

	/**
	 * Divides the \em time duration from of this instance by \em divider.
	 * @param divider The divider.
	 * @return A reference to the modified TimeDuration instance.
	 */
	TimeDuration<Implementation>& operator/=(int divider)
	{
		Implementation::operator/=(divider);
		return *this;
	}

	/**
	 * Gets the hours represented in this instance.
	 */
	int hours() const
	{
		return Implementation::hours();
	}
	/**
	 * Gets the minutes represented in this instance.
	 */
	int minutes() const
	{
		return Implementation::minutes();
	}
	/**
	 * Gets the seconds represented in this instance.
	 */
	int seconds() const
	{
		return Implementation::seconds();
	}
	/**
	 * Gets the milliseconds represented in this instance.
	 */
	int milliseconds() const
	{
		return Implementation::milliseconds();
	}
	/**
	 * Gets the microseconds represented in this instance.
	 */
	int microseconds() const
	{
		return Implementation::microseconds();
	}
	/**
	 * Gets the nanoseconds represented in this instance.
	 */
	int nanoseconds() const
	{
		return Implementation::nanoseconds();
	}

	/**
	 * Sets the hours represented in this instance.
	 */
	void hours(int newHours)
	{
		Implementation::hours(newHours);
	}
	/**
	 * Sets the minutes represented in this instance.
	 */
	void minutes(int newMinutes)
	{
		Implementation::minutes(newMinutes);
	}
	/**
	 * Sets the seconds represented in this instance.
	 */
	void seconds(int newSeconds)
	{
		Implementation::seconds(newSeconds);
	}
	/**
	 * Sets the milliseconds represented in this instance.
	 */
	void milliseconds(int newMilliSeconds)
	{
		Implementation::milliseconds(newMilliSeconds);
	}
	/**
	 * Sets the microseconds represented in this instance.
	 */
	void microseconds(int newMicroSeconds)
	{
		Implementation::microseconds(newMicroSeconds);
	}
	/**
	 * Sets the nanoseconds represented in this instance.
	 */
	void nanoseconds(int newNanoSeconds)
	{
		Implementation::nanoseconds(newNanoSeconds);
	}

	/**
	 * Gets the native "real"-time duration representation.
	 * @return
	 */
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
