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

	oss << "\nTask: " << name << '\n'
		<< description << '\n'
		<< "Start Date: " << getStartDate() << '\n'
		<< "Deadline: " << getDeadline() << '\n';
	
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
	oss << '\n' << "Time allocations belonging to the '" << name << "' Task\n";

	// Cycle through each of the time allocations and add them to the oss.
	for (auto t : TAs)
	{
		oss << t->getDetails();
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

