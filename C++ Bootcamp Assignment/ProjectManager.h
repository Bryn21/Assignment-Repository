#pragma once
#include "MainHeaderFiles.h"
#include <algorithm>
#include <fstream>

enum TimeAllocationType
{
	MeetingTA,
	WorkDoneTA,
	BugFixTA,
	ResearchTA,
};

class ProjectManager
{
public:
	ProjectManager();
	ProjectManager(std::string newFileName);
	~ProjectManager();

	// Prints the name of the current text file being used.
	void printFileName() const;

	// Returns a string with all of the project information to be displayed.
	// The string will be formatted ready to output.
	std::string printProject(bool reverseValue = false);

	// Returns a string with only the time allocations for this project
	// The string will be formatted ready to output.
	std::string printTAs(bool reverseValue = false);

	// Returns a string containing the details of a specific time allocation.
	// The string will be formatted ready to output.
	std::string printTADetails(std::string taskName, int TANumber);

	// Returns a string containing all of the tasks and passes a reference for the list of task names.
	// The string will be formtatted ready to output.
	std::string printTasks(std::vector<std::string> &tasksVector) const;

	// Returns a string containing the details of a specific task.
	// The string will be formatted ready for output.
	std::string printTaskDetails(std::string taskName);

	// Returns a string containing all of the TAs for this specific task.
	// The string will be formatted ready for output.
	std::string printTaskTAs(std::string taskName, int &TACount);

	// Returns a string containing the details of the current project.
	// The string will be formatted ready to output.
	std::string printProjectDetails() const;

	// Returns a string containing the details of all the projects.
	// The string will be formatted ready to output.
	std::string printAllProjectDetails() const;

	// Get the total number of projects in the project manager.
	int numberOfProjects() const;

	// Save the project management information to the current text file being used.
	void save() const;

	// Load the project management information from the current text file being used. 
	// Returns a string containing the project information for each project in the file.
	void load();

	// Change to use a new text file.
	void changeTextFile(std::string newTextFile);

	// Setup the current text file for use.
	void setupFile();

	// Returns a string containing the relative file path.
	std::string getFilePath()  const { return "../TextFiles/" + fileName; };

	// Set the current project being used by assigning a value to the projectPointer.
	// The project number should be the position of the project within the projects vector, not the index.
	// The project at the front of projects is projectNumber '1'.
	void setProjectPointer(int projectNumber);

	// Create a project.
	void createProject(std::string start = "01/01/2016 00:00", std::string end = "01/01/2017 00:00", std::string name = "New Project", std::string description = "Project management");

	// Create a task and add it to the project.
	void createTask(std::string start, std::string end, std::string name, std::string description);

	// Create a Meeting Time allocation and add it to a task.
	void createMeeting(std::string start, std::string end, std::string location, std::string attendees, std::string taskName);

	// Create a WorkDone Time allocation and add it to a task.
	void createWorkDone(std::string start, std::string end, std::string description, std::string taskName);

	// Create a BugFix Time allocation and add it to a task (Using string bugID).
	void createBugFix(std::string start, std::string end, std::string bugID, std::string description, std::string taskName);

	// Create a BugFix Time allocation and add it to a task (Using int bugID).
	void createBugFix(std::string start, std::string end, int bugID, std::string description, std::string taskName);

	// Create a Research Time allocation and add it to a task.
	void createResearch(std::string start, std::string end, std::string description, std::string taskName);

	// Delete a project.
	void deleteCurrentProject();

	// Delete a task.
	void deleteTask(std::string taskName);

	// Delete a time allocation.
	// The TANumber is the number for the Time Alloction within the list.
	// If there is one Time Allocation in the list then the TANumber would be 1.
	void deleteTA(std::string taskName, int TANumber);

private:
	// Default file being used is "Project.txt".
	std::string fileName = "Project.txt";

	// Value used to point to the current project being used from the projects vector.
	// -1 until there is a project created to easily keep the correct index value.
	int projectPointer = -1;

	// A vector of all the projects loaded in.
	std::vector<Project> projects = {};
};

// Overloaded << operator for output of the project.
std::ostream& operator << (std::ostream& os, ProjectManager& projectManager);

