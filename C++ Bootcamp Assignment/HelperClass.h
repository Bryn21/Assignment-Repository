#pragma once
#include "DateTime.h"

#define EL '\n'

// Helper namespace for some multi purpose functions.
namespace Helper
{
	// Converts a given integer value (minutes) into a string format for the time.
	// Returns a string in the form 'HH Hours and MM minutes' ready to be output.
	std::string MinutesToTime(int minutes);
}