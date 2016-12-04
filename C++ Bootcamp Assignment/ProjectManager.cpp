#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
	// Setup the current text file using the default text file name.
	setupFile();
}

ProjectManager::ProjectManager(std::string newFileName)
{
	// If name is empty then use the default fileName.
	if (newFileName == "")
	{
		setupFile();
	}
	else
	{
		// Change the file name and make sure it ends with '.txt'
		changeTextFile(newFileName);

		// Setup the current text file using the default text file name.
		setupFile();
	}
}

ProjectManager::~ProjectManager()
{
}

std::ostream& operator << (std::ostream& os, ProjectManager& projectManager)
{
	// Slightly redundant as it simply calls the print project function but it still adds the << operator functionality.
	os << projectManager.printProject();
	return os;
}

void ProjectManager::printFileName()
{
	std::cout << "\nThe current text file being used is " << fileName << '\n';
}

std::string ProjectManager::printProject(bool reverseValue)
{
	// Set the reverse flag in the project.
	project.reverse = reverseValue;

	// Add the project to the oss.
	std::ostringstream oss;	
	oss << project;

	// Reset the reverse flag.
	project.reverse = false;
	
	// Return the oss as a string.
	return oss.str();
}

std::string ProjectManager::printTAs(bool reverseValue)
{
	// Set the reverse flag in the project.
	project.reverse = reverseValue;

	// Add the project TAs to the oss.
	std::ostringstream oss;
	oss << project.getTAsString();

	// Return the oss as a string.
	return oss.str();
}

std::string ProjectManager::printTasks(std::vector<std::string> &tasksVector)
{
	return project.getTasks(tasksVector);
}

std::string ProjectManager::printTaskDetails(std::string taskName)
{
	return project.getTask(taskName)->getDetails();
}

std::string ProjectManager::printProjectDetails()
{
	return project.getDetails();
}

void ProjectManager::save()
{
	std::fstream inout(getFilePath(), std::ios::out);

	// Save the project to the text file.
	inout << "Project" << EL;
	inout << project.save();		

	// Go through the tasks and save them ot the text file.
	for (auto t : project.getTasks())
	{
		inout << "Task" << EL;
		inout << t.save();		

		// Go through the time allocations for the task and save them to the text file.
		for (auto ta : t.getTAs())
		{
			inout << "TA" << EL;
			inout << ta->save();
		}
	}

	inout.close();

	//std::cout << EL << "File saved to " << fileName << EL;
}

Project& ProjectManager::load()
{
	std::fstream inout(getFilePath(), std::ios::in);
	std::string start, end, name, description, text;

	while (!inout.eof())
	{
		// Text used to determine next action.
		std::getline(inout, text);

		if (text == "TA")
		{
			// Text used to determine TA type.
			std::getline(inout, text);

			if (text == "Meeting")
			{
				std::getline(inout, start);
				std::getline(inout, end);
				std::getline(inout, text);			// Use text as location.
				std::getline(inout, description);	// Use description as attendees.

				// Use name as the task name.
				createMeeting(start, end, text, description, name);
			}
			else if (text == "WorkDone")
			{
				std::getline(inout, start);
				std::getline(inout, end);
				std::getline(inout, description);

				// Use name as the task name.
				createWorkDone(start, end, description, name);
			}
			else if (text == "BugFix")
			{
				std::getline(inout, start);
				std::getline(inout, end);
				std::getline(inout, text);			// Use text as bugID.
				std::getline(inout, description); 

				// Use name as the task name.
				createBugFix(start, end, text, description, name);
			}			
		}
		else if (text == "Task")
		{
			std::getline(inout, start);
			std::getline(inout, end);
			std::getline(inout, name);
			std::getline(inout, description);

			createTask(start, end, name, description);
		}
		else if (text == "Project")
		{
			std::getline(inout, start);
			std::getline(inout, end);
			std::getline(inout, name);
			std::getline(inout, description);

			createProject(start, end, name, description);
		}
	}

	inout.close();

	return project;
}

void ProjectManager::createProject(std::string start, std::string end, std::string name, std::string description)
{	
	project = Project(start, end, name, description);
}

void ProjectManager::createTask(std::string start, std::string end, std::string name, std::string description)
{
	Task task(start, end, name, description);

	if (!project.checkTask(name))
	{
		project.addTask(task);
	}
}

void ProjectManager::createMeeting(std::string start, std::string end, std::string location, std::string attendees, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (project.checkTask(taskName))
	{
		tempTask = project.getTask(taskName);
		
		// TODO - Pointer issue?
		Meeting* meeting = new Meeting(start, end, location, attendees);
		tempTask->addTimeAllocation(meeting);
	}
}

void ProjectManager::createWorkDone(std::string start, std::string end, std::string description, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (project.checkTask(taskName))
	{
		tempTask = project.getTask(taskName);
		
		// TODO - Pointer issue?
		WorkDone* workDone = new WorkDone(start, end, description);
		tempTask->addTimeAllocation(workDone);
	}
}

void ProjectManager::createBugFix(std::string start, std::string end, std::string bugID, std::string description, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (project.checkTask(taskName))
	{
		tempTask = project.getTask(taskName);
		int ID = std::stoi(bugID);

		// TODO - Pointer issue?
		BugFix* bugFix = new BugFix(start, end, ID, description);
		tempTask->addTimeAllocation(bugFix);
	}
}

void ProjectManager::createBugFix(std::string start, std::string end, int bugID, std::string description, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (project.checkTask(taskName))
	{
		tempTask = project.getTask(taskName);

		// TODO - Pointer issue?
		BugFix* bugFix = new BugFix(start, end, bugID, description);
		tempTask->addTimeAllocation(bugFix);
	}
}

void ProjectManager::changeTextFile(std::string newFileName)
{
	if (newFileName.find(".txt") == std::string::npos)
	{
		newFileName.append(".txt");
	}

	fileName = newFileName;

	// Setup the new text file.
	setupFile();
}

void ProjectManager::setupFile()
{
	std::fstream inout(getFilePath(), std::ios::app);	

	inout.close();

	load();
}

