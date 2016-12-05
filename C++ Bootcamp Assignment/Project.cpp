#include "Project.h"

Project::Project()
	: startDate(""), deadline(""), name(""), description(""), tasks({})
{
}

Project::Project(std::string start,	std::string end, std::string projectName, std::string projectDescription)
	: startDate(start), deadline(end), name(projectName), description(projectDescription), tasks({})
{
}

Project::~Project()
{
}

std::ostream& operator << (std::ostream& os, Project& project)
{
	os << project.getDetails();
	os << EL << "Total time spent on this project: " << Helper::MinutesToTime(project.getTotalProjectTime()) << EL;
	os << project.getTasksString();
	
	return os;
}

// Returns the formatted start date for the project as a string.
std::string Project::getStartDate()
{
	return startDate.getFormatted();
}

// Returns the formatted deadline date for the project as a string.
std::string Project::getDeadline()
{
	return deadline.getFormatted();
}

// Returns a string containing the details for the project.
// The string is formatted ready to output.
std::string Project::getDetails()
{
	std::ostringstream oss;

	oss << "\nProject: " << name << '\n'
		<< description << '\n'
		<< "Start Date: " << getStartDate() << '\n'
		<< "Deadline: " << getDeadline() << '\n';

	return oss.str();
}

void Project::addTask(Task task)
{
	tasks.push_back(task);
}

void Project::addTimeAllocationToTask(Task task, TimeAllocation *ta)
{
	for (auto &t : tasks)
	{
		if (t.getTaskName() == task.getTaskName())
		{
			t.addTimeAllocation(ta);
		}
	}
}

std::string Project::getTasksString()
{
	std::ostringstream oss;

	// Add the name of the project to the oss.
	oss  << EL << "     Tasks belonging to " << name << ":" << EL;

	// int for numbering the tasks in the list.
	int taskNumber = 0;

	// Output the tasks names and while doing this set the reverse flags for each task.
	for (auto &t : tasks)
	{
		t.reverse = reverse;
		oss << EL << "     " << ++taskNumber << ". " << t.getTaskName();
	}

	oss << EL;

	// Output the TA information for each task. This loop will make use of the reverse flag. 
	for (auto t : tasks)
	{
		oss << t;
	}

	// Reset the reverse flag.
	for (auto &t : tasks)
	{
		t.reverse = false;
	}

	return oss.str();

	// TODO - The tasks need to be returned in a particular order (time order?).
}

std::string Project::getTasks(std::vector<std::string> &tasksVector)
{
	std::ostringstream oss;

	// Add the name of the project to the oss.
	oss << EL << "     Tasks belonging to " << name << ":" << EL;

	// Make sure the taskVecotr is clear ready to add the tasks.
	tasksVector.clear();

	for (auto t : tasks)
	{
		tasksVector.push_back(t.getTaskName());
		oss << EL << "     Task number: " << tasksVector.size();
		oss << t.getDetails();
	}

	if (tasksVector.size() == 0)
	{
		oss.clear();
		oss << EL << "     There are currently no tasks in the project" << EL;
	}

	return oss.str();
}

std::string Project::getTAsString()
{
	std::ostringstream oss;

	// Add the name of the project to the oss.
	oss << EL << "          Time allocations belonging to " << name << ":" << EL;

	// int for numbering the tasks in the list.
	int taskNumber = 0;
	std::vector<TimeAllocation*> tas;

	// Output the tasks names and while doing this set the reverse flags for each task.
	for (auto &t : tasks)
	{
		for (auto i : t.getTAs())
		{
			tas.push_back(i);
		}
	}

	if (reverse)
	{
		// Sort from newest at the top to oldest at the bottom.
		std::sort(tas.begin(), tas.end(), [](TimeAllocation* lhs, TimeAllocation* rhs) { return (lhs->getStartDateTime() > rhs->getStartDateTime()); });
	}
	else
	{
		// Sort from oldest at the top to newest at the bottom.
		std::sort(tas.begin(), tas.end(), [](TimeAllocation* lhs, TimeAllocation* rhs) { return (lhs->getStartDateTime() < rhs->getStartDateTime()); });
	}

	for (auto i : tas)
	{
		oss << *i;
	}

	return oss.str();
}

Task* Project::getTask(std::string taskName)
{
	for (auto &t : tasks)
	{
		if (t.getTaskName() == taskName)
		{			
			return &t;
		}
	}

	std::cout << "\nThere is no task with the name '" << taskName << "'";

	return nullptr;
}

bool Project::checkTask(std::string taskName)
{
	for (auto &t : tasks)
	{
		if (t.getTaskName() == taskName)
		{
			return true;
		}
	}

	return false;
	std::cout << "\nThere is no task with the name '" << taskName << "'";
}

std::string Project::save()
{
	std::ostringstream oss;

	oss << startDate.getFormatted() << EL
		<< deadline.getFormatted() << EL
		<< name << EL
		<< description << EL;

	return oss.str();
}

int Project::getTotalProjectTime()
{
	int projectTime = 0;

	// Loop through each of the tasks.
	for (auto i : tasks)
	{
		// Add the total task time for the total project time in minutes.
		projectTime += i.getTotalTaskTime();
	}

	// Return the project time in minutes.
	return projectTime;
}