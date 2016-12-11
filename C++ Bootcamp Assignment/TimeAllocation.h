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
	virtual std::string getDetails() const = 0 ;

	// Returns a string containing the type of TA this object is.
	virtual std::string getType() const = 0;

	// Returns the formatted start date for this time allocation.
	std::string getStartDate() const;

	// Returns the formatted end date for this time allocation.
	std::string getEndDate() const;

	// Return the time from the start to the finish of the time allocation (in minutes).
	int getDuration() const;

	// Create a string used to save the time allocation.
	virtual std::string save() const  = 0;

	// Get the start date time to do comparisons.
	DateTime getStartDateTime() const;

	bool operator==(TimeAllocation*);

private:
	DateTime startDateTime;
	DateTime endDateTime;
};

std::ostream& operator << (std::ostream& os, TimeAllocation& time);

