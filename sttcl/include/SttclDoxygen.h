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
 * \ref uml2gof_sec "3 Mapping of the UML state diagram notation elements to the GoF State pattern"
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
 * \ref usage_sec_1 "2.1 Declare a StateMachine implementation"\n
 * \ref usage_sec_2 "2.2 Declare State implementations"\n
 * \ref usage_sec_3 "2.3 Implement the state machine interfaces"\n
 * \ref usage_sec_4 "2.4 Implement state actions and transitions"\n
 *
 * \subsection usage_sec_1 2.1 Declare a StateMachine implementation
 *
 * Analyze your UML 2.2 state diagram and declare all necessary variables and event (trigger
 * methods) needed for the state machine. Declare an appropriate instance of \c sttcl::StateMachine<>
 * as base class for your state machine class.
 *
 * \code
class MyStateMachine;

class IStateEventHandlers
{
public:
	virtual handleEvent1(MyStateMachine* context) = 0;
	virtual handleEvent2(MyStateMachine* context) = 0;
};

class MyStateMachine : public sttcl::StateMachine<MyStateMachine,IStateEventHandlers>
{
public:
	void event1();
	void event2();

	int getX() const;
	const std::string& getY();

	// ...
};
\endcode
 *
 * According to the GoF state pattern implementation variants you can decide where to hold the
 * necessary state instances and make their sibling states accessible for them, so they can
 * realize event triggered transitions.
 * As a rule of thumb the state implementation classes can be instantiated as singletons (see
 * <A HREF="http://en.wikipedia.org/wiki/Singleton_Pattern">GoF Singleton pattern</A>) if they
 * have no member variables other than application scope configurations. Otherwise the available
 * states should be embedded members of the state machine implementation class and are accessible
 * from the state machine context for state implementation classes.
 *
 * \note State implementation classes inheriting from the sttcl::ActiveState<>
 * or sttcl::CompositeState<> template classes implicitly have embedded members in the base
 * classes.
 *
 * \subsection usage_sec_2 2.2 Declare State implementations
 * Implement a state class for each state in your UML 2.2 state machine diagram. Declare the
 * appropriate instance of the sttcl::State<> template class as base class for all state classes.
 * \code
class MyStateMachine;

class MyState1 : public sttcl::State<MyState1,MyStateMachine,IStateEventHandlers>
{
	// ...
};
\endcode
 *
 * \subsection usage_sec_3 2.3 Implement state machine interface
 *
 * The event1() and event2() method implementations of MyStateMachine can just delegate to the
 * matching call to the IStateEventHandlers interface of the current state
 * \code
void MyStateMachine::event1()
{
	IStateEventHandlers* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent1(this);
	}
}
\endcode
 *
 * \subsection usage_sec_4 2.4 Implement state actions and transitions
 *
 * Transition actions are implemented within the event handler methods of the state classes.
 */

/**
 * \page uml2gof_page Mapping of the state diagram notation elements
 * \section uml2gof_sec 3 Mapping of the UML state diagram notation elements to the GoF State pattern
 * \htmlinclude UMLStateGoFStateMapping.html
 *
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
