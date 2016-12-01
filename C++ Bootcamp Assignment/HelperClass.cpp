#include "HelperClass.h"

namespace Helper
{
	std::string MinutesToTime(int totalMinutes)
	{
		// Seperate the minutes into hours and minutes.
		int Minutes = totalMinutes % 60;
		int Hours = (totalMinutes - Minutes) / 60;

		// Create a oss for the return string.
		std::ostringstream oss;

		// String holding the hours and minutes string text. Both default to plural.
		std::string HoursStr(" Hours "), MinutesStr(" Minutes ");

		// If Hours is singular then edit the text.
		if (Hours == 1)
		{
			HoursStr = " Hour ";
		}

		// If Minutes is singular then edit the text.
		if (Minutes == 1)
		{
			MinutesStr = " Minute ";
		}

		// Add the informtation to the oss and return as a string.
		oss << Hours << HoursStr << Minutes << MinutesStr;
		return oss.str();
	}
}