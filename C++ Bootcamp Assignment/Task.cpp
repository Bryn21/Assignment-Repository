#include "Task.h"
#include <memory>

Task::Task()
	:startDate(""), deadline(""), name(""), description(""), TAs({})
{
}

Task::Task(std::string start, std::string end, std::string taskName, std::string taskDescription)
	: startDate(start), deadline(end), name(taskName), description(taskDescription), TAs({})
{
}

Task::~Task()
{
}

std::ostream& operator << (std::ostream& os, Task& task)
{
	os << task.getDetails();
	os << task.getTAsString();
	return os;
}

bool Task::operator==(const Task &task)
{
	if (name == task.name &&
		description == task.description)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns the formatted start date for the task as a string.
std::string Task::getStartDate() const
{
	return startDate.getFormatted();
}

// Returns the formatted deadline date for the task as a string.
std::string Task::getDeadline() const
{
	return deadline.getFormatted();
}

// Returns a string containing the details for the task.
// The string is formatted ready to output.
std::string Task::getDetails()  const
{
	std::ostringstream oss;

	oss << "\n     Task: " << name << EL
		<< "     " << description << EL
		<< "     Start Date: " << getStartDate() << EL
		<< "     Deadline: " << getDeadline() << EL
		<< "     Time spent on this task: " << Helper::MinutesToTime(getTotalTaskTime()) << EL;
	
	return oss.str();
}

std::string Task::getTADetails(int TANumber)  const
{
	return TAs[TANumber - 1]->getDetails();
}

void Task::addTimeAllocation(TimeAllocation *ta)
{		
	TAs.push_back(ta);
	sortTAOrder();
}

void Task::deleteTimeAllocation(int TANumber)
{
	// Create a temporary pointer to the Time Allocation.
	TimeAllocation * ta = TAs[TANumber - 1];

	// Erase the TA using the erase-remove idiom.
	TAs.erase(std::remove(TAs.begin(), TAs.end(), ta), TAs.end());
}

std::string Task::getTAsString() 
{
	int TACount = 0;

	return getTAsString(TACount);
}

std::string Task::getTAsString(int &TACount) 
{
	std::ostringstream oss;

	// Add the name of the task to the oss.
	oss << EL << "          Time allocations belonging to " << name << ":" << EL;

	// int for numbering the TA's in the list.
	TACount = 0;

	// Reverse the order of the list for output.
	if (reverse)
	{
		std::reverse(TAs.begin(), TAs.end());
	}

	for (auto ta : TAs)
	{
		oss << EL << "          " << ++TACount << ". " << ta->getType();
	}

	oss << EL;

	// Cycle through each of the time allocations and add them to the oss.
	for (auto ta : TAs)
	{
		oss << *ta;
	}

	// Reverse the order of the list back to the original order.
	if (reverse)
	{
		std::reverse(TAs.begin(), TAs.end());
	}

	return oss.str();
}

std::string Task::save()  const
{
	std::ostringstream oss;

	oss << startDate.getFormatted() << EL
		<< deadline.getFormatted() << EL
		<< name << EL
		<< description << EL;

	return oss.str();
}

int Task::getTotalTaskTime()  const
{
	int taskTime = 0;

	// Loop through the task allocations to get the duration of each.
	for (auto i : TAs)
	{
		// Add these times to the taskTime which will be in minutes.
		taskTime += i->getDuration();
	}

	// Return the task time as the total number of minutes.
	return taskTime;
}

void Task::sortTAOrder()
{
	// Sort from newest at the top to oldest at the bottom.
	std::sort(TAs.begin(), TAs.end(), [](TimeAllocation* lhs, TimeAllocation* rhs) { return (lhs->getStartDateTime() > rhs->getStartDateTime()); });
}

