#pragma once
#include "TimeAllocation.h"

class Meeting : public TimeAllocation
{
public:
	// The dates are in the format 'DD/MM/YYYY HH:MM'
	// NamesOfAttendees seperate by ', '
	Meeting(std::string start, 
		    std::string end, 
		    std::string theLocation, 
		    std::string namesOfAttendees);

	~Meeting();

	// Returns a string containing the details of the meeting.
	// The string will be formatted ready to output.
	std::string getDetails();

private:
	std::string location;
	std::string listOfAttendees;
};

