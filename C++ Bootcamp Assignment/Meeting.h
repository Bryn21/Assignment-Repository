#pragma once
#include "GeneralHeaderFiles.h"

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

	// Return a string with the type of TA.
	std::string getType() { return "Meeting"; };

	// Create a string used to save the meeting to a text file.
	std::string save();

private:
	std::string location;
	std::string listOfAttendees;
};

