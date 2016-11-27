#include "Meeting.h"

Meeting::Meeting(std::string start, std::string end, std::string theLocation, std::string namesOfAttendees)
	: TimeAllocation(start, end), location(theLocation), listOfAttendees(namesOfAttendees)
{
}

Meeting::~Meeting()
{
}

std::string Meeting::getDetails()
{
	std::ostringstream oss;	

	oss << "\n          Meeting\n"
		<< "          Location: " << location << '\n'
		<< "          Attendees: " << listOfAttendees << '\n'
		<< "          Date: " << getStartDate() << '\n'
		<< "          Time taken: " << getDuration() << " Minutes\n";

	return oss.str();
}

std::string Meeting::save()
{
	std::ostringstream oss;

	oss << "Meeting" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< location << EL
		<< listOfAttendees << EL;

	return oss.str();
}
