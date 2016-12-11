#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "HelperClass.h"

class DateTime
{
public:
	DateTime();
	~DateTime();
	DateTime(std::string);			   // Parse from a string format.
	std::string getFormatted() const;  // Return as a formatted string.
	int getIntTime() const;			   // Return the hour-minutes time in just minutes.

	bool operator>(const DateTime&);
	bool operator<(const DateTime&);

private:
	int minute; // 0 to 59
	int hour;   // 0 to 23
	int day;    // 1 to 31
	int month;  // 1 to 12
	int year;
};


