#include "TimeAllocation.h"

TimeAllocation::TimeAllocation()
	: startDateTime("01/01/2016 12:00"), endDateTime("01/01/2016 13:00")
{
}

TimeAllocation::TimeAllocation(std::string start, std::string end)
	: startDateTime(start), endDateTime(end)
{
}

TimeAllocation::~TimeAllocation()
{
}

std::ostream& operator << (std::ostream& os, TimeAllocation& time)
{
	os << time.getDetails();
	return os;
}

bool TimeAllocation::operator==(TimeAllocation *ta)
{
	if (getDetails() == ta->getDetails())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns the formatted start date for this time allocation.
std::string TimeAllocation::getStartDate()
{
	return startDateTime.getFormatted();
}

// Returns the formatted end date for this time allocation.
std::string TimeAllocation::getEndDate()
{
	return endDateTime.getFormatted();
}

// Return the time from the start to the finish of the time allocation.
int TimeAllocation::getDuration()
{
	int start(startDateTime.getIntTime());
	int end(endDateTime.getIntTime());

	// If start is less than end then the times went over midnight.
	// For this case we add 1 day to the start time, in minutes.
	if (start > end)
	{
		end += 1440; // 1 day in minutes, 24 * 60. 
	}

	//TODO - If there is more than a day difference between the start and end time then this time taken returned will be incorrect.

	return end - start;
}

DateTime TimeAllocation::getStartDateTime()
{
	return startDateTime;
}
