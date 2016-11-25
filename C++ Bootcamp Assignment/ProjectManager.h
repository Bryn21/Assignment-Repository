#pragma once
#include "MainHeaderFiles.h"
#include <algorithm>
#include <fstream>

enum TimeAllocationType
{
	MeetingTA,
	WorkDoneTA,
	BugFixTA,
};

class ProjectManager
{
public:
	ProjectManager();
	~ProjectManager();

	// Prints the name of the current text file being used.
	void printFileName();

	// Save the project management information to the current text file being used.
	void save();

	// Load the project management information from the current text file being used. 
	// Returns a reference to the project.
	Project& load();

	// Change to use a new text file.
	void changeTextFile(std::string newTextFile);

	// Setup the current text file for use.
	void setupFile();

	// Create a project.
	void createProject(std::string start, std::string end, std::string name, std::string description);
	// Create a task and add it to the project.
	void createTask(std::string start, std::string end, std::string name, std::string description);
	// Create a Meeting Time allocation and add it to a task.
	void createMeeting(std::string start, std::string end, std::string location, std::string attendees, std::string taskName);

private:
	// Default file being used is "ProjectManagementAssignment.txt".
	std::string fileName = "ProjectManagementAssignment.txt";

	// The current project loaded in from the text file.
	Project project;

	
};

