#include "Meeting.h"

Meeting::Meeting(std::string start, std::string end, std::string theLocation, std::string namesOfAttendees)
	: TimeAllocation(start, end), location(theLocation), listOfAttendees(namesOfAttendees)
{
}

Meeting::~Meeting()
{
}

std::string Meeting::getDetails() const
{
	std::ostringstream oss;	

	oss << "\n          Meeting\n"
		<< "          Location: " << location << EL
		<< "          Attendees: " << listOfAttendees << EL
		<< "          Date: " << getStartDate() << EL
		<< "          Time taken: " << Helper::MinutesToTime(getDuration()) << EL;

	return oss.str();
}

std::string Meeting::save() const
{
	std::ostringstream oss;

	oss << "Meeting" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< location << EL
		<< listOfAttendees << EL;

	return oss.str();
}
