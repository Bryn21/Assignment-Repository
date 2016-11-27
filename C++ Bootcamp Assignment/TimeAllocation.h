#pragma once
#include <iostream>
#include "DateTime.h"

class TimeAllocation
{
public:
	TimeAllocation();
	TimeAllocation(std::string start, std::string end);
	~TimeAllocation();	

	// Returns a string containing the details of the time allocation.
	// The string will be formatted ready to output.
	virtual std::string getDetails() = 0;

	// Returns a string containing the type of TA this object is.
	virtual std::string getType() = 0;

	// Returns the formatted start date for this time allocation.
	std::string getStartDate();

	// Returns the formatted end date for this time allocation.
	std::string getEndDate();

	// Return the time from the start to the finish of the time allocation.
	int getDuration();

	// Create a string used to save the time allocation.
	virtual std::string save() = 0;

private:
	DateTime startDateTime;
	DateTime endDateTime;
};

