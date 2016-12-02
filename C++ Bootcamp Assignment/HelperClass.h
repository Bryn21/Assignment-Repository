#pragma once
#include "DateTime.h"

#define EL '\n'

// Helper namespace for some multi purpose functions.
namespace Helper
{
	// Converts a given integer value (minutes) into a string format for the time.
	// Returns a string in the form 'HH Hours and MM minutes' ready to be output.
	std::string MinutesToTime(int minutes);

	// Check if a specified string is a valid format for DateTime.
	bool IsValidDateTime(std::string string);

	// Adds time to a given string that is in a valid format of dateTime.
	// timeToAdd must be less than 1440 and more than 0.
	std::string AddTimeToDateTime(std::string dateTime, int timeToAdd);
}