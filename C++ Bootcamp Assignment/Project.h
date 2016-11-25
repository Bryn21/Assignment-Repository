#pragma once
#include "GeneralHeaderFiles.h"

class Project
{
public:
	Project();
	// The dates are in the format 'DD/MM/YYYY HH:MM'
	Project(std::string start,
			std::string end,
			std::string projectName,
			std::string projectDescription);
	~Project();

	const auto getTasks() { return tasks; };

	// Returns a string containing the details of the project.
	// The details will be the name, description, start date and deadline.
	// The string will be formatted ready to output.
	std::string getDetails();
	// Returns the formatted start date for the project as a string.
	std::string getStartDate();
	// Returns the formatted deadline date for the project as a string.
	std::string getDeadline();

	// Add a task to the project.
	void addTask(Task task);
	// Add a TA to a particular task.
	void addTimeAllocationToTask(Task task, TimeAllocation *ta);

	// Returns a string containing eash of the tasks in the project.
	// The string will be formatted ready to output.
	std::string getTasksString();

	// Get a task from the project and use a pointer to edit it.
	Task* getTask(std::string taskName);

	// Check if a task is in the project.
	bool checkTask(std::string taskName);

	// Create a string used to save the project to the text file.
	std::string save();

private:
	DateTime startDate;
	DateTime deadline;
	std::string name;
	std::string description;
	std::vector<Task> tasks;
};

