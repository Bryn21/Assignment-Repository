#pragma once
#include "TimeAllocation.h"
#include "Task.h"
#include <vector>

class Project
{
public:
	// The dates are in the format 'DD/MM/YYYY HH:MM'
	Project(std::string start,
			std::string end,
			std::string projectName,
			std::string projectDescription);
	~Project();

	// Returns a string containing the details of the project.
	// The details will be the name, description, start date and deadline.
	// The string will be formatted ready to output.
	std::string getDetails();
	// Returns the formatted start date for the project as a string.
	std::string getStartDate();
	// Returns the formatted deadline date for the project as a string.
	std::string getDeadline();

	void addTask(Task task);

	void addTimeAllocationToTask(Task task, TimeAllocation *ta);

	// Returns a string containing eash of the tasks in the project.
	// The string will be formatted ready to output.
	std::string getTasks();

private:
	DateTime startDate;
	DateTime deadline;
	std::string name;
	std::string description;
	std::vector<Task> tasks;
};

