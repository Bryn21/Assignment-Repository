#pragma once
#include "GeneralHeaderFiles.h"

class Research : public TimeAllocation
{
public:
	// The dates are in the format 'DD/MM/YYYY HH:MM'.
	Research(std::string start,
		std::string end,
		std::string researchDescription);

	~Research();

	// Returns a string containing the details of the work done.
	// The string will be formatted ready to output.
	std::string getDetails();

	// Return a string with the type of TA.
	std::string getType() { return "Research"; };

	// Create a string used to save the work done to a text file.
	std::string save();

private:
	// A brief description of the work done. 
	std::string description;
};

