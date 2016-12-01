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

// Returns the formatted start date for the task as a string.
std::string Task::getStartDate()
{
	return startDate.getFormatted();
}

// Returns the formatted deadline date for the task as a string.
std::string Task::getDeadline()
{
	return deadline.getFormatted();
}

// Returns a string containing the details for the task.
// The string is formatted ready to output.
std::string Task::getDetails()
{
	std::ostringstream oss;

	oss << "\n     Task: " << name << EL
		<< "     " << description << EL
		<< "     Start Date: " << getStartDate() << EL
		<< "     Deadline: " << getDeadline() << EL
		<< "     Time spent on this task: " << Helper::MinutesToTime(getTotalTaskTime()) << EL;
	
	return oss.str();
}

void Task::addTimeAllocation(TimeAllocation *ta)
{		
	TAs.push_back(ta);
}

std::string Task::getTAsString()
{
	std::ostringstream oss;

	// Add the name of the task to the oss.
	oss << EL << "          Time allocations belonging to " << name << ":" << EL;

	// int for numbering the TA's in the list.
	int TANumber = 0;

	// Reverse the order of the list for output.
	if (reverse)
	{
		std::reverse(TAs.begin(), TAs.end());
	}

	for (auto ta : TAs)
	{
		oss << EL << "          " << ++TANumber << ". " << ta->getType();
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

	// TODO - The time allocations need to be returned in time order (and reverse time order).
}

std::string Task::save()
{
	std::ostringstream oss;

	oss << startDate.getFormatted() << EL
		<< deadline.getFormatted() << EL
		<< name << EL
		<< description << EL;

	return oss.str();
}

int Task::getTotalTaskTime()
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

