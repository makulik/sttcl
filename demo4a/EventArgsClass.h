/*
 * EventArgsClass.h
 *
 *  Created on: 14.03.2012
 *      Author: Admin
 */

#ifndef EVENTARGSCLASS_H_
#define EVENTARGSCLASS_H_

#include <string>

namespace Application
{

class EventArgsClass
{
public:
	EventArgsClass(const std::string& argData);
	virtual ~EventArgsClass();

	const std::string& getData() const
	{
		return data;
	}
private:
	std::string data;
};

} /* namespace Application */
#endif /* EVENTARGSCLASS_H_ */
