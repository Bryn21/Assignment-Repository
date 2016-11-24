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
	std::string getStartDate();
	std::string getEndDate();
	int getDuration();

private:
	DateTime startDateTime;
	DateTime endDateTime;
};

