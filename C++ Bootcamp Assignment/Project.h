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

	// Changed from auto return type to run on C++11
	std::vector<Task> getTasks() { return tasks; };

	// Returns a string containing the details of the project.
	// The details will be the name, description, start date and deadline.
	// The string will be formatted ready to output.
	std::string getDetails();
	// Returns the formatted start date for the project as a string.
	std::string getStartDate();
	// Returns the formatted deadline date for the project as a string.
	std::string getDeadline();
	// Returns the name of the project.
	std::string getProjectName() { return name; }

	// Add a task to the project.
	void addTask(Task task);
	// Add a TA to a particular task.
	void addTimeAllocationToTask(Task task, TimeAllocation *ta);

	// Delete a task from the project.
	void deleteTask(Task *task);

	// Delete a TA from a task.
	void deleteTimeAllocation(Task *task, int TANumber);


	// Returns a string containing the tasks and passes a reference back for the names of the tasks.
	// The string will be formatted ready to output.
	std::string getTasks(std::vector<std::string> &tasksVector);

	// Returns a string containing eash of the tasks in the project.
	// The string will be formatted ready to output.
	std::string getTasksString();

	// Returns a string containing only the time allocations from the project.
	// The string will be formatted ready to output.
	std::string getTAsString();

	// Get a task from the project and use a pointer to edit it.
	Task* getTask(std::string taskName);

	// Check if a task is in the project.
	bool checkTask(std::string taskName);

	// Create a string used to save the project to the text file.
	std::string save();

	// Get the total time for the tasks in the project (in minutes).
	int getTotalProjectTime();

	// bool used for showing the TA's in reverse order.
	bool reverse = false;

	bool operator==(const Project&);

private:
	DateTime startDate;
	DateTime deadline;
	std::string name;
	std::string description;
	std::vector<Task> tasks;
};

std::ostream& operator << (std::ostream& os, Project& project);
