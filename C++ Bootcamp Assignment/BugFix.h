#pragma once
#include "GeneralHeaderFiles.h"

class BugFix : public TimeAllocation
{
public:
	// The dates are in the format 'DD/MM/YYYY HH:MM'.
	// The bug ID is a integer number with no spaces.
	BugFix(std::string start, 
		   std::string end, 
		   int bugID, 
		   std::string bugDescription);

	~BugFix();

	// Returns a string containing the details of the bug fix.
	// The string will be formatted ready to output.
	std::string getDetails() const;

	// Return a string with the type of TA.
	std::string getType() const { return "Bug Fix"; };

	// Create a string used to save the bug fix to a text file.
	std::string save() const;

private:
	// ID number for the bug.
	int ID;
	// A description of the fix for the bug.
	std::string description;
};

