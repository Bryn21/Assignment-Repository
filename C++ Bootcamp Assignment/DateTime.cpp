#include "DateTime.h"

DateTime::DateTime()
{
}


DateTime::~DateTime()
{
}


DateTime::DateTime(std::string datetime)
{
	// DD/MM/YYYY HH:MM
	std::istringstream iss(datetime);
	char dump;
	iss >> day >> dump >> month >> dump >> year >> hour >> dump >> minute;
}

std::string DateTime::getFormatted() const
{
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

// Return the hour-minutes time in just minutes.
int DateTime::getIntTime() const
{
	return ((hour * 60) + minute);
}

bool DateTime::operator > (const DateTime &dateTime)
{
	if (year > dateTime.year)
	{
		return true;
	}
	else if (year < dateTime.year)
	{
		return false;
	}

	if (month > dateTime.month)
	{
		return true;
	}
	else if (month < dateTime.month)
	{
		return false;
	}

	if (day > dateTime.day)
	{
		return true;
	}
	else if (day < dateTime.day)
	{
		return false;
	}

	if (hour > dateTime.hour)
	{
		return true;
	}
	else if (hour < dateTime.hour)
	{
		return false;
	}

	if (minute > dateTime.minute)
	{
		return true;
	}
	else if (minute < dateTime.minute)
	{
		return false;
	}

	// If the dates are the same then return false.
	return false;
}

bool DateTime::operator < (const DateTime &dateTime)
{
	if (year > dateTime.year)
	{
		return false;
	}
	else if (year < dateTime.year)
	{
		return true;
	}

	if (month > dateTime.month)
	{
		return false;
	}
	else if (month < dateTime.month)
	{
		return true;
	}

	if (day > dateTime.day)
	{
		return false;
	}
	else if (day < dateTime.day)
	{
		return true;
	}

	if (hour > dateTime.hour)
	{
		return false;
	}
	else if (hour < dateTime.hour)
	{
		return true;
	}

	if (minute > dateTime.minute)
	{
		return false;
	}
	else if (minute < dateTime.minute)
	{
		return true;
	}

	// If the dates are the same then return false.
	return false;
}
