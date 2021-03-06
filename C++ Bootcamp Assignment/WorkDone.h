#pragma once
#include "GeneralHeaderFiles.h"

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
	std::string getDetails() const;

	// Return a string with the type of TA.
	std::string getType() const { return "Work Done"; };

	// Create a string used to save the work done to a text file.
	std::string save() const;

private:
	// A brief description of the work done. 
	std::string description;
};

