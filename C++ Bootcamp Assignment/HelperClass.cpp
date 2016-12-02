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

	bool IsValidDateTime(std::string string)
	{
		// DD/MM/YYYY HH:MM
		std::istringstream iss(string);
		char dump;
		int day, month, year, hour, minute;
		iss >> day >> dump >> month >> dump >> year >> hour >> dump >> minute;

		// Check if the minute value is valid.
		if (minute > 59 || minute < 0)
		{
			return false;
		}

		// Check if the hour value is valid.
		if (hour > 24 || hour < 0)
		{
			return false;
		}

		// Month modifier for the different months.
		int monthModifier = 0;

		if (month == (11 || 9 || 6 || 4))
		{
			monthModifier = 1;
		}
		else if (month == 2)
		{
			monthModifier = 3;
		}

		// Check if the day value is valid using the month modifier.
		if (day < 1 || day > (31 - monthModifier))
		{
			return false;
		}

		// Check if the month value is valid.
		if (month < 1 || month > 12)
		{
			return false;
		}

		// Check if the year value is valid.
		if (year < 2016 || year > 2018)
		{
			return false;
		}

		// If all checks passed then the DateTime is valid.
		return true;
	}

	std::string AddTimeToDateTime(std::string dateTime, int timeToAdd)
	{
		// DD/MM/YYYY HH:MM
		std::istringstream iss(dateTime);
		char dump;
		int day, month, year, hour, minute;
		iss >> day >> dump >> month >> dump >> year >> hour >> dump >> minute;

		// Only add if the timeToAdd is in the correct range.
		if (timeToAdd < 1440 && timeToAdd > 0)
		{
			int minutesToAdd = timeToAdd % 60;
			int hoursToAdd = (timeToAdd - minutesToAdd) / 60;

			// Add the minutes.
			if (minute + minutesToAdd >= 60)
			{
				hour++;
				minute = (minute + minutesToAdd - 60);
			}
			else
			{
				minute += minutesToAdd;
			}

			// Add the hours.
			if (hour + hoursToAdd >= 24)
			{
				day++;
				hour = (hour + hoursToAdd - 24);
			}
			else
			{
				hour += hoursToAdd;
			}

			// Month modifier for the different months.
			int monthModifier = 0;

			if (month == (11 || 9 || 6 || 4))
			{
				monthModifier = 1;
			}
			else if (month == 2)
			{
				monthModifier = 3;
			}

			// Edit the day and month if the day goes past.
			if (day > (31 - monthModifier))
			{
				day = 1;
				month++;
			}

			// Edit the month and year if the month goes past.
			if (month > 12)
			{
				month = 1;
				year++;
			}
		}

		// DD/MM/YYYY HH:MM
		std::ostringstream oss;
		oss << std::setfill('0');
		oss << std::setw(2) << day << '/';
		oss << std::setw(2) << month << '/';
		oss << year << ' ';
		oss << std::setw(2) << hour << ':';
		oss << std::setw(2) << minute;
		return oss.str();
	}
}