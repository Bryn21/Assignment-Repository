#include "MainHeaderFiles.h"
#include "ProjectManager.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	// Resize the console window.
	HWND console = GetConsoleWindow();
	MoveWindow(console, 200, 20, 800, 1000, TRUE);

	std::cout << EL << "C++ bootcamp assignment" << EL;

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

	std::cout << EL << "Press enter to start" << EL;

	std::cin.get();

	system("CLS");

	// Loop through the menu and the menu functionality until 0 is entered (to break out of the loop).
	while (true)
	{
		std::cout << pm.printProjectDetails();
		std::cout << EL << "Menu options:" << EL;
		std::cout << EL << "'1' - Display current project.";
		std::cout << EL << "'2' - Load file or create new file. ";
		std::cout << EL << "'3' - Display only the time allocations.";
		std::cout << EL << "'4' - Add a time allocation.";
		std::cout << EL << "'5' - Save the currently loaded project.";

		std::cout << EL << EL << "'0' - Quit" << EL;

		// Get the input from the user and determine the value entered.
		// If the value is not a valid option then the default case will be called.
		std::string input;
		std::cin >> input;
		int value = std::stoi(input);

		// Quit out when 0 is entered.
		if (value == 0) break;

		// Clear the screen to display new information.
		system("CLS");

		// Output the details of the current project.
		std::cout << pm.printProjectDetails();

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

				// Clear the screen to display new information.
				system("CLS");

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
				std::cout << EL << "Enter filename to load or new filename to create";
				std::cout << EL << "New files will be created with default project descriptions" << EL << EL;
				std::cin >> input;
				pm.changeTextFile(input);
				pm.load();
				std::cout << EL << "'" << input << "' loaded successfully." << EL;
				break;
			}
			case 3:
			{
				// Should the time allocations be shown in ascending or descending order?
				std::cout << EL << "'1' - Display project with oldest time allocation first";
				std::cout << EL << "'2' - Display project with newest time allocation first" << EL;

				// Get the input from the user.
				std::cin >> input;
				int value2 = std::stoi(input);

				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

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
			case 4:
			{
				while (true)
				{
					// Used to store a list of task names.
					std::vector<std::string> tasksVector = {};

					// Get all of the tasks in the project.
					std::cout << pm.printTasks(tasksVector);

					if (tasksVector.size() == 0)
					{
						break;
					}

					std::cout << EL << "     Which task would you like to add a time allocation to?";
					std::cout << EL << "     If you no longer wish to add a TA then please enter '0'." << EL << EL;

					std::cout << EL << "     Please enter the task number:";

					// Get the input from the user.
					std::cin >> input;
					int taskNumber = std::stoi(input);

					// Valid value has been entered.
					if (taskNumber <= tasksVector.size() && taskNumber > 0)
					{
						// Clear the screen to display new information.
						system("CLS");

						// Output the details of the current project.
						std::cout << pm.printProjectDetails();

						// Output the chosen task.
						std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

						// Time Allocation types are explicitly wrote out and created without any loops.
						// If a significant amount of different types of Time Allocation were added to the system then this would not be good.
						std::cout << EL << "     What type of time allocation would you like to add?";
						std::cout << EL << EL << "     '1' - Meeting";
						std::cout << EL << "     '2' - Work Done";
						std::cout << EL << "     '3' - Bug Fix";
						// std::cout << EL << "     '4 - Other";

						std::cout << EL << EL << "     If you no longer wish to add a TA then please enter '0'." << EL << EL;

						std::cout << EL << "     Please enter the TA type number:";

						// Get the input from the user.
						std::cin >> input;
						int TAType = std::stoi(input);

						// User wishes to cancel.
						if (TAType == 0)
						{
							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();
							break;
						}
						// Valid value has been entered. (4 is the number of Time Allocation types. Explicitly entered here which is bad)
						else if (TAType <= 4 && TAType > 0)
						{
							// Again, no loops are used which would be bad if many Time Allocation types were introduced to the system.

							// Collect information that applies for all types of Time Allocation.
							std::string TAStartDate, TAEndDate;
							int TADuration;

							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();

							// Output the chosen task.
							std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

							std::cin.ignore();

							while (true)
							{	
								std::cout << EL << "     Please enter the start date (DD/MM/YYYY HH:MM)" << EL << EL;
								std::cout << "     ";

								// Get the input from the user.
								std::getline(std::cin, TAStartDate);

								if (Helper::IsValidDateTime(TAStartDate))
								{
									break;
								}
								else
								{
									std::cout << EL << "     Invalid date entered" << std::endl;
								}
							}

							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();

							// Output the chosen task.
							std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

							while (true)
							{
								std::cout << EL << "     Please enter the duration of the time allocation in minutes." << EL << "     Duration must be higher than 0 and lower than 1440." << EL << EL;
								std::cout << "     ";

								// Get the input from the user.
								std::cin >> input;
								TADuration = std::stoi(input);								

								if (TADuration < 0 || TADuration > 1439)
								{
									std::cout << EL << "     Invalid duration entered" << std::endl;
								}
								else
								{
									break;
								}
							}		

							// Determine the end date using the start date and the duration.
							TAEndDate = Helper::AddTimeToDateTime(TAStartDate, TADuration);

							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();

							// Output the chosen task.
							std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

							std::cin.ignore();

							// Meeting
							if (TAType == 1)
							{
								std::string location, listOfAttendees;

								std::cout << EL << "     Please enter the location" << EL;
								std::cout << EL << "     ";								

								// Get the input from the user.
								std::getline(std::cin, location);

								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();

								// Output the chosen task.
								std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

								std::cout << EL << "     Please enter the list of attendees" << EL;
								std::cout << EL << "     ";

								// Get the input from the user.
								std::getline(std::cin, listOfAttendees);

								// Add the meeting.
								pm.createMeeting(TAStartDate, TAEndDate, location, listOfAttendees, tasksVector[taskNumber - 1]);								
							}
							// Work Done
							else if (TAType == 2)
							{
								std::string workDescription;

								std::cout << EL << "     Please enter the description for the work done" << EL;
								std::cout << EL << "     ";

								// Get the input from the user.
								std::getline(std::cin, workDescription);

								// Add the work done.
								pm.createWorkDone(TAStartDate, TAEndDate, workDescription, tasksVector[taskNumber - 1]);
							}
							// Bug Fix
							else if (TAType == 3)
							{
								int bugID;
								std::string bugDescription;

								std::cout << EL << "     Please enter the bugID. Must be above 0" << EL;
								std::cout << EL << "     ";

								// Get the input from the user.
								std::cin >> input;
								bugID = std::stoi(input);

								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();

								// Output the chosen task.
								std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

								std::cout << EL << "     Please enter the description for the bug fix" << EL;
								std::cout << EL << "     ";

								std::cin.ignore();

								// Get the input from the user.
								std::getline(std::cin, bugDescription);

								// Add the bug fix
								pm.createBugFix(TAStartDate, TAEndDate, bugID, bugDescription, tasksVector[taskNumber - 1]);
							}
							// Other
							else if (TAType == 4)
							{
								std::cout << "     Other not available yet" << EL;
								break;
							}
						}
						else
						{
							std::cout << EL << "     Invalid TA number entered" << EL;

							std::cin.ignore();
							std::cin.get();
						}

						// Clear the screen to display new information.
						system("CLS");

						// Output the details of the current project.
						std::cout << pm.printProjectDetails();

						std::cout << EL << "     Successfully added." << EL;

						while (true)
						{
							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();

							std::cout << EL << "     Would you like to save the project? y / n" << EL << EL;
							std::cout << "     ";

							std::cin >> input;

							if (input == "y")
							{
								// Save the textfile.
								pm.save();

								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();

								std::cout << EL << "Project successfully saved" << EL;
								break;
							}
							else if (input == "n")
							{
								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();
								break;
							}
							else
							{
								std::cout << EL << "     Invalid choice" << EL;
								std::cout << EL << "     Press enter to choose again";
								std::cin.ignore();
								std::cin.get();
							}
						}
						break;
					}
					else if (taskNumber == 0)
					{
						// Clear the screen to display new information.
						system("CLS");

						// Output the details of the current project.
						std::cout << pm.printProjectDetails();
						break;
					}
					else
					{
						std::cout << EL << "     Invalid task number entered" << EL;
						std::cout << EL << "     Press enter to continue..." << EL;

						std::cin.ignore();
						std::cin.get();
					}
				}
				break;
			}
			case 5:
			{
				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				// Save the current project.
				pm.save();

				std::cout << EL << "Project successfully saved" << EL;
				break;
			}
			default:
			{
				// Invalid option has been chosen.
				std::cout << EL << "Invalid menu option!" << EL;
			}
		}

		std::cout << EL << "Press enter to continue..." << std::endl;
		
		std::cin.ignore();
		std::cin.get();

		// Clear the screen to display new information.
		system("CLS");
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