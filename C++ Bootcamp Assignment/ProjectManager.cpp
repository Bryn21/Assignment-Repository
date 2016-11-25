#include "ProjectManager.h"

ProjectManager::ProjectManager()
{
	// Setup the current text file using the default text file name.
	setupFile();
}

ProjectManager::~ProjectManager()
{
}

void ProjectManager::printFileName()
{
	std::cout << "\nThe current text file being used is " << fileName << '\n';
}

void ProjectManager::save()
{
	std::fstream inout(fileName, std::ios::out);

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

	std::cout << EL << "File saved to " << fileName << EL;
}

Project& ProjectManager::load()
{
	std::fstream inout(fileName, std::ios::in);
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
				// Use text as the task name.
				createMeeting(start, end, text, description, name);
			}
			else if (text == "WorkDone")
			{
				std::getline(inout, start);
				std::getline(inout, end);
			}
			else if (text == "BugFix")
			{
				std::getline(inout, start);
				std::getline(inout, end);
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
		// TODO - Maybe scope problem with the unique pointer.
		Meeting* meeting = new Meeting(start, end, location, attendees);
		tempTask->addTimeAllocation(meeting);
	}
}

void ProjectManager::changeTextFile(std::string newFileName)
{
	// TODO Save changes to the old text file first? - Maybe ask the user?

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
	std::fstream inout(fileName, std::ios::app);
	inout.close();
}

