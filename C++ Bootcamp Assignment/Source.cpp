#include "MainHeaderFiles.h"
#include "ProjectManager.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	// Resize the console window.
	HWND console = GetConsoleWindow();
	MoveWindow(console, 200, 20, 800, 1000, TRUE);

	std::cout << "C++ bootcamp assignment" << EL;

	// FileName defaults to an empty string.
	std::string fileNameInput = "";

	// There should be 2 arguments entered, the .exe for the project and the new file name.
	if (argc == 2) 
	{
		// argv[1] should be the filename to open. 
		// argv[0] should be the .exe for the project.
		fileNameInput = argv[1];
	}	

	// If an empty string is passed in then the default filename is used.
	ProjectManager pm(fileNameInput);	

	// Loop through the menu and the menu functionality until 0 is entered (to break out of the loop).
	while (true)
	{
		std::cout << EL << "Menu options:" << EL;
		std::cout << EL << "'1' - Display current project.";
		std::cout << EL << "'2' - Load new file.";
		std::cout << EL << "'3' - Display only the time allocations.";

		std::cout << EL << EL << "'0' - Quit" << EL;

		// Get the input from the user and determine the value entered.
		// If the value is not a valid option then the default case will be called.
		std::string input;
		std::cin >> input;
		int value = std::stoi(input);

		// Quit out when 0 is entered.
		if (value == 0) break;

		switch (value)
		{
			case 1:
			{
				// Should the time allocations be shown in ascending or descending order?
				std::cout << EL << "'1' - Display project with time allocations in ascending order";
				std::cout << EL << "'2' - Display project with time allocations in decending order" << EL;

				// Get the input from the user.
				std::cin >> input;
				int value2 = std::stoi(input);

				if (value2 == 2)
				{
					// Print the project in decending order.
					std::cout << pm.printProject(true);
				}
				else if (value2 != 1)
				{
					std::cout << EL << "Invalid option entered. Displaying with ascending order";
				}
				else
				{
					// Print the project in ascending order.
					std::cout << pm.printProject();
				}
				break;
			}
			case 2:
			{
				// Load a new file.
				std::cout << EL << "Enter new file to load: ";
				std::cin >> input;
				pm.changeTextFile(input);
				std::cout << EL << "'" << input << "' loaded successfully." << EL;
				break;
			}
			case 3:
			{
				// Should the time allocations be shown in ascending or descending order?
				std::cout << EL << "'1' - Display project with time allocations in ascending order";
				std::cout << EL << "'2' - Display project with time allocations in decending order" << EL;

				// Get the input from the user.
				std::cin >> input;
				int value2 = std::stoi(input);

				if (value2 == 2)
				{
					// Print the project in decending order.
					std::cout << pm.printTAs(true);
				}
				else if (value2 != 1)
				{
					std::cout << EL << "Invalid option entered. Displaying with ascending order";
				}
				else
				{
					// Print the project in ascending order.
					std::cout << pm.printTAs();
				}
				break;
			}
			default:
			{
				// Invalid option has been chosen.
				std::cout << EL << "Invalid menu option!" << EL;
			}
		}
	}
}

// STUFF

//Project project("11/12/2016 12:15", "11/12/2016 13:15", "Project 1", "Description of the project");

//Task task("11/12/2016 12:15", "11/12/2016 13:15", "Task 1", "Description of the task");

//project.addTask(task);

//// TODO - Scope problem with the unique pointers.
//auto meeting = std::make_unique<Meeting>("11/12/2016 12:15", "11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell");

//project.addTimeAllocationToTask(task, meeting.get());

//auto workDone = std::make_unique<WorkDone>("11/12/2016 12:15", "11/12/2016 13:15", "Did some work on the assignment");
//auto bugFix = std::make_unique<BugFix>("11/12/2016 12:15", "11/12/2016 13:15", 1, "Fixed a bug with a DateTime problem");

// Meeting meeting = ("11/12/2016 12:15","11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell");
// WorkDone workDone("11/12/2016 12:15", "11/12/2016 13:15", "Did some work on the assignment");
// BugFix bugFix("11/12/2016 12:15", "11/12/2016 13:15", 1, "Fixed a bug with a DateTime problem");


//project.addTimeAllocationToTask(task, workDone.get());
//project.addTimeAllocationToTask(task, bugFix.get());

/*pm.createProject("11/12/2016 12:15", "11/12/2016 13:15", "Project 1", "Description of the project");

pm.createTask("11/12/2016 12:15", "11/12/2016 13:15", "Task 1", "Description of the task");

pm.createTask("11/12/2016 12:15", "11/12/2016 13:15", "Task 2", "Description of the task");

pm.createMeeting("11/12/2016 12:15", "11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell", "Task 1");

pm.createWorkDone("11/12/2016 12:15", "11/12/2016 13:15", "Work done description", "Task 1");

pm.createBugFix("11/12/2016 12:15", "11/12/2016 13:15", 1, "Bug Fix Description", "Task 1");

pm.createBugFix("11/12/2016 12:15", "11/12/2016 13:15", 2, "Bug Fix Description", "Task 2");

pm.save();*/