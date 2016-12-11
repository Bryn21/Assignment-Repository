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

void ProjectManager::printFileName() const
{
	std::cout << "\nThe current text file being used is " << fileName << '\n';
}

std::string ProjectManager::printProject(bool reverseValue)
{
	// Set the reverse flag in the project.
	projects[projectPointer].reverse = reverseValue;

	// Add the project to the oss.
	std::ostringstream oss;	
	oss << projects[projectPointer];

	// Reset the reverse flag.
	projects[projectPointer].reverse = false;
	
	// Return the oss as a string.
	return oss.str();
}

std::string ProjectManager::printTAs(bool reverseValue)
{
	// Set the reverse flag in the project.
	projects[projectPointer].reverse = reverseValue;

	// Add the project TAs to the oss.
	std::ostringstream oss;
	oss << projects[projectPointer].getTAsString();

	// Return the oss as a string.
	return oss.str();
}

std::string ProjectManager::printTADetails(std::string taskName, int TANumber)
{
	return projects[projectPointer].getTask(taskName)->getTADetails(TANumber);
}

std::string ProjectManager::printTasks(std::vector<std::string> &tasksVector) const
{
	return projects[projectPointer].getTasks(tasksVector);
}

std::string ProjectManager::printTaskDetails(std::string taskName)
{
	return projects[projectPointer].getTask(taskName)->getDetails();
}

std::string ProjectManager::printTaskTAs(std::string taskName, int &TACount)
{
	return projects[projectPointer].getTask(taskName)->getTAsString(TACount);
}

std::string ProjectManager::printProjectDetails() const
{
	return projects[projectPointer].getDetails();
}

std::string ProjectManager::printAllProjectDetails() const
{
	std::ostringstream oss;
	int pNum = 0;

	// Add the name of the project to the oss.
	oss << EL << "The projects loaded in from '" << getFilePath() << "' are:" << EL;;

	for (auto p : projects)
	{
		oss << EL << "Project number: " << ++pNum ;
		oss << p.getDetails();
	}

	if (projects.size() == 0)
	{
		oss.clear();
		oss << EL << "The file loaded in contains no projects" << EL;
	}

	return oss.str();
}

int ProjectManager::numberOfProjects() const
{
	return projects.size();
}

void ProjectManager::save() const
{
	std::fstream inout(getFilePath(), std::ios::out);

	for (auto p : projects)
	{
		// Save the project to the text file.
		inout << "Project" << EL;
		inout << p.save();

		// Go through the tasks and save them ot the text file.
		for (auto t : p.getTasks())
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
	}

	inout.close();
}

void ProjectManager::load()
{
	std::fstream inout(getFilePath(), std::ios::in);
	std::string start, end, name, description, text;

	projectPointer = -1;
	projects.clear();

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
			else if (text == "Research")
			{
				std::getline(inout, start);
				std::getline(inout, end);		
				std::getline(inout, description);

				// Use name as the task name.
				createResearch(start, end, description, name);
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
}

void ProjectManager::setProjectPointer(int projectNumber)
{
	projectPointer = projectNumber - 1;

	// If project pointer is not a valud number then by default use the first project.
	if (projectPointer > projects.size() || projectPointer < -1)
	{
		// Re assign the value to be 0.
		projectPointer = 0;
	}
}

void ProjectManager::createProject(std::string start, std::string end, std::string name, std::string description)
{	
	projects.push_back(Project(start, end, name, description));
	projectPointer++;
}

void ProjectManager::createTask(std::string start, std::string end, std::string name, std::string description)
{
	Task task(start, end, name, description);

	if (!projects[projectPointer].checkTask(name))
	{
		projects[projectPointer].addTask(task);
	}
}

void ProjectManager::createMeeting(std::string start, std::string end, std::string location, std::string attendees, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (projects[projectPointer].checkTask(taskName))
	{
		tempTask = projects[projectPointer].getTask(taskName);
		
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
	if (projects[projectPointer].checkTask(taskName))
	{
		tempTask = projects[projectPointer].getTask(taskName);
		
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
	if (projects[projectPointer].checkTask(taskName))
	{
		tempTask = projects[projectPointer].getTask(taskName);
		int ID = std::stoi(bugID);

		BugFix* bugFix = new BugFix(start, end, ID, description);
		tempTask->addTimeAllocation(bugFix);
	}
}

void ProjectManager::createBugFix(std::string start, std::string end, int bugID, std::string description, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (projects[projectPointer].checkTask(taskName))
	{
		tempTask = projects[projectPointer].getTask(taskName);

		BugFix* bugFix = new BugFix(start, end, bugID, description);
		tempTask->addTimeAllocation(bugFix);
	}
}

void ProjectManager::createResearch(std::string start, std::string end, std::string description, std::string taskName)
{
	// Create a pointer to point to the task.
	Task* tempTask;

	// Only add the meeting if the task exists.
	if (projects[projectPointer].checkTask(taskName))
	{
		tempTask = projects[projectPointer].getTask(taskName);

		Research* research = new Research(start, end, description);
		tempTask->addTimeAllocation(research);
	}
}

void ProjectManager::deleteCurrentProject()
{
	// Erase the project using the erase-remove idiom.
	projects.erase(std::remove(projects.begin(), projects.end(), projects[projectPointer]), projects.end());
}

void ProjectManager::deleteTask(std::string taskName)
{
	projects[projectPointer].deleteTask(projects[projectPointer].getTask(taskName));
}

void ProjectManager::deleteTA(std::string taskName, int TANumber)
{
	projects[projectPointer].deleteTimeAllocation(projects[projectPointer].getTask(taskName), TANumber);
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

