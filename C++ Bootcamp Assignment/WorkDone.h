#pragma once
#include "TimeAllocation.h"

class WorkDone : public TimeAllocation
{
public:
	// The dates are in the format 'DD/MM/YYYY HH:MM'.
	WorkDone(std::string start, 
		     std::string end, 
		     std::string workDescription);

	~WorkDone();

	// Returns a string containing the details of the work done.
	// The string will be formatted ready to output.
	std::string getDetails();

private:
	// A brief description of the work done. 
	std::string description;
};

