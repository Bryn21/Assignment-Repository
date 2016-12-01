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
	ProjectManager(std::string newFileName);
	~ProjectManager();

	// Prints the name of the current text file being used.
	void printFileName();

	// Returns a string with all of the project information to be displayed.
	// The string will be formatted ready to output.
	std::string printProject(bool reverseValue = false);

	// Returns a string with only the time allocations for this project
	// The string will be formatted ready to output.
	std::string printTAs(bool reverseValue = false);

	// Save the project management information to the current text file being used.
	void save();

	// Load the project management information from the current text file being used. 
	// Returns a reference to the project.
	Project& load();

	// Change to use a new text file.
	void changeTextFile(std::string newTextFile);

	// Setup the current text file for use.
	void setupFile();

	// Returns a string containing the relative file path.
	std::string getFilePath() { return "../TextFiles/" + fileName; };


	// Create a project.
	void createProject(std::string start, std::string end, std::string name, std::string description);

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

private:
	// Default file being used is "ProjectTextFile.txt".
	std::string fileName = "Project.txt";

	// The current project loaded in from the text file.
	Project project;	
};

std::ostream& operator << (std::ostream& os, ProjectManager& projectManager);

