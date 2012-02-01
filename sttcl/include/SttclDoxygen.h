/*
 * SttclDoxygen.hpp
 *
 *  Created on: 01.02.2012
 *      Author: Admin
 */

#ifndef STTCLDOXYGEN_HPP_
#define STTCLDOXYGEN_HPP_

/*! \mainpage STTCL state machine template class framework
 *
 * Content:\n
 * \ref intro_sec "1 Introduction"\n
 * \ref usage_sec "2 Usage of the STTCL state machine template class framework"\n
 * \ref usage_sec_1 "2.1 Declare a StateMachine implementation"\n
 * \ref usage_sec_2 "2.2 Declare State implementations"\n
 * \ref usage_sec_3 "2.3 Implement the state machine interfaces"\n
 * \ref usage_sec_4 "2.4 Implement state actions and transitions"\n
 *
 * \section intro_sec 1 Introduction
 *
 * The STTCL state machine template class framework provides a number of template classes to
 * implement UML 2.2 state machine specification compliant state machines. The template classes
 * are intended to be used as public base class of the implementation of state machine and state
 * classes. The basic function principle is based on the <A HREF="http://en.wikipedia.org/wiki/State_pattern" >GoF State Pattern</A>.
 *
 * You start with a given UML 2.2 state diagram that defines your applications behavior:
 * \image html StateMachine_Implementation_SD.png "State machine diagram"
 *
 * The GoF state pattern proposes to use a class design like shown in the following class diagram.
 * \image html StateMachine_Implementation_CD.png "State machine implementation class diagram"
 *
 * The overall class design using STTCL will look like the following detailed class diagram:
 * \image html Application_Design_CD.png "STTCL state machine application design class diagram"
 */

/**
 * \page usage_page Usage of the STTCL state machine template class framework
 * \section usage_sec 2 Usage of the STTCL state machine template class framework
 *
 * \subsection usage_sec_1 2.1 Declare a StateMachine implementation
 *
 * \subsection usage_sec_2 2.2 Declare State implementations
 *
 * \subsection usage_sec_3 2.3 Implement state machine interface
 *
 * \subsection usage_sec_4 2.4 Implement state actions and transitions
 */

/**
 * @namespace sttcl
 * @brief Provides base classes to build state machines.
 */
namespace sttcl
{

/**
 * @namespace sttcl::internal
 * @brief Classes used internally by the STTCL implementation
 */
namespace internal
{

/**
 * @namespace sttcl::internal::boost_impl
 * @brief Contains boost based implementation classes for STTCL.
 */
namespace boost_impl
{
}

/**
 * @namespace sttcl::internal::posix_impl
 * @brief Contains posix based implementation classes for STTCL.
 */
namespace posix_impl
{
}

}
}

#endif /* STTCLDOXYGEN_HPP_ */
