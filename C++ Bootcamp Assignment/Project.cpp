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
	oss << '\n' << "Tasks belonging to the '" << name << "' Project\n";

	for (auto t : tasks)
	{
		oss << t.getDetails();
		oss << t.getTAsString();
	}

	return oss.str();

	// TODO - The tasks need to be returned in a particular order (time order?).
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