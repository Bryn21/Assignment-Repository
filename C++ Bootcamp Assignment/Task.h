#pragma once
#include "GeneralHeaderFiles.h"
#include "Meeting.h"

class Task
{
public:
	Task();
	// The dates are in the format 'DD/MM/YYYY HH:MM'
	Task(std::string start, 
		 std::string end, 
		 std::string taskName, 
		 std::string taskDescription);
	
	~Task();

	// Changed from auto return type to run on C++11.
	const std::vector<TimeAllocation*> getTAs() { return TAs; };

	// Returns a string containing the details of the task.
	// The details will be the name, task description, start date and deadline.
	// The string will be formatted ready to output.
	std::string getDetails();
	// Returns the formatted start date for the task as a string.
	std::string getStartDate();
	// Returns the formatted deadline date for the task as a string.
	std::string getDeadline();
	// Returns the name of the task.
	std::string getTaskName() { return name; }

	void addTimeAllocation(TimeAllocation *ta);

	// Returns a string containing each of the time allocations that have been carried out for this task.
	// The string will be formatted ready to output.
	std::string getTAsString();

	// Create a string used to save the task to the text file.
	std::string save();

	// The total time spent on all of the time allocations for this task (in minutes).
	int getTotalTaskTime();

	// Sort the time allocations into the correct order, from earliest to latest.
	void sortTAOrder();

	// Bool used to display the Time Allocations in reverse.
	bool reverse = false;

private:
	DateTime startDate;
	DateTime deadline;
	std::string name;
	std::string description;
	std::vector<TimeAllocation*> TAs;
};

std::ostream& operator << (std::ostream& os, Task& task);

