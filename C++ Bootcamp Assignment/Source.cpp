#include "MainHeaderFiles.h"
#include "ProjectManager.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	// Function declarations.

	void chooseProject(ProjectManager& pm);
	void createNewProject(ProjectManager& pm);

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

	chooseProject(pm);

	system("CLS");

	// Loop through the menu and the menu functionality until 0 is entered (to break out of the loop).
	while (true)
	{
		std::cout << pm.printProjectDetails();
		std::cout << EL << "Menu options:" << EL;
		std::cout << EL << "'1'  - Display current project.";		
		std::cout << EL << "'2'  - Display only the time allocations for the current project.";
		std::cout << EL << "'3'  - Add a new time allocation.";
		std::cout << EL << "'4'  - Add a new task.";
		std::cout << EL << "'5'  - Add a new project.";
		std::cout << EL << "'6'  - Delete a time allocation.";
		std::cout << EL << "'7'  - Delete a task.";
		std::cout << EL << "'8'  - Delete the current project.";
		std::cout << EL << "'9'  - Save changes made to the project.";
		std::cout << EL << "'10' - Choose another project from the text file. ";
		std::cout << EL << "'11' - Load file or create a new file. ";
		

		std::cout << EL << EL << "'0' - Quit" << EL << EL;

		// Get the input from the user and determine the value entered.
		// If the value is not a valid option then the default case will be called.
		std::string input;
		std::cin >> input;
		int value;

		// Try catch statement for error checking.
		try
		{
			// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
			value = std::stoi(input);

		}
		catch (...)
		{
			// Exception. Assign -1 in order to access the default case for an invalid choice.
			value = -1;
		}

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
				std::cout << EL << "'2' - Display project with time allocations in decending order" << EL << EL;

				// Get the input from the user.
				std::cin >> input;
				int value2;

				// Try catch statement for error checking.
				try
				{
					// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
					value2 = std::stoi(input);

				}
				catch (...)
				{
					// Exception. Assign 0 to follow the 'Invalid option entered' else statement.
					value2 = 0;
				}

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
			case 10:
			{
				chooseProject(pm);
				break;
			}
			case 11:
			{

				// Clear the screen to display new information.
				system("CLS");

				// Load a new file.
				std::cout << EL << "Enter filename to load or new filename to create" << EL;
				std::cin >> input;

				// Change the text file in the project manager.
				pm.changeTextFile(input);

				int length = 0;

				// Open the text file.
				std::fstream inout(pm.getFilePath(), std::ios::app);	

				// Check if the file is empty. If the file is empty then a new file has been created.
				inout.seekg(0, std::ios::end);
				length = inout.tellg();

				inout.close();				

				// Determine if the text file is empty or contains an already existing project.
				if (length == 0)
				{	
					std::string startDate, deadLine, name, description;

					std::cout << EL << "New file '" << pm.getFilePath() << "' created." << EL;
					std::cout << EL << "The new file needs a project" << EL;

					while (true)
					{
						std::cout << EL << "Please enter a name for the Project" << EL << EL;

						std::cin.ignore();

						// Get the input from the user.
						std::getline(std::cin, name);

						// Clear the screen to display new information.
						system("CLS");

						std::cout << EL << "Please enter a description for the project" << EL << EL;

						// Get the input from the user.
						std::getline(std::cin, description);

						// Clear the screen to display new information.
						system("CLS");

						while (true)
						{
							std::cout << EL << "Please enter a start date for the project (DD/MM/YYYY HH:MM)" << EL << EL;

							// Get the input from the user.
							std::getline(std::cin, startDate);

							if (Helper::IsValidDateTime(startDate))
							{
								break;
							}
							else
							{
								std::cout << EL << "Invalid date entered" << std::endl;
							}
						}

						// Clear the screen to display new information.
						system("CLS");

						while (true)
						{
							std::cout << EL << "Please enter a deadline date for the project (DD/MM/YYYY HH:MM)" << EL << EL;

							// Get the input from the user.
							std::getline(std::cin, deadLine);

							if (Helper::IsValidDateTime(deadLine))
							{
								break;
							}
							else
							{
								std::cout << EL << "Invalid date entered" << std::endl;
							}
						}

						bool answer = true;

						bool currentAnswer = answer;

						// Clear the screen to display new information.
						system("CLS");

						std::cout << EL << "These details have been entered:" << EL;
						std::cout << "Name: " << name << EL
							<< "Description: " << description << EL
							<< "Start Date: " << startDate << EL
							<< "Deadline: " << deadLine << EL;

						std::cout << EL << "Are these details correct?" << EL << "Type 'y' for yes and 'n' for no" << EL;							

						std::cin >> input;

						// Project pointer set to 0 as there are no projects added yet.
						// pm.setProjectPointer(0);

						if (input == "y")
						{				
							// Create project will set the project pointer to 1.
							pm.createProject(startDate, deadLine, name, description);
							pm.save();

							// Clear the screen to display new information.
							system("CLS");

							std::cout << EL << "The project has been created and saved successfully" << EL;							

							break;								
						}
						else
						{
							// Clear the screen to display new information.
							system("CLS");

							std::cout << EL << "Would you like to enter the information again?" << EL << "Type 'y' for yes and 'n' for no" << EL;

							std::cin >> input;

							if (input != "y")
							{
								std::cout << EL << "The project has been created with default values" << EL;

								// Create project will set the project pointer to 1.
								pm.createProject();
								pm.save();
								break;
							} 

							// Clear the screen to display new information.
							system("CLS");
						}
					}
				}
				else
				{
					pm.load();
					std::cout << EL << "'" << input << "' loaded successfully." << EL;

					chooseProject(pm);
				}
				break;
			}
			case 2:
			{
				// Should the time allocations be shown in ascending or descending order?
				std::cout << EL << "'1' - Display project with oldest time allocation first";
				std::cout << EL << "'2' - Display project with newest time allocation first" << EL << EL;

				// Get the input from the user.
				std::cin >> input;
				int value2;

				// Try catch statement for error checking.
				try
				{
					// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
					value2 = std::stoi(input);

				}
				catch (...)
				{
					// Exception. Assign 0 to follow the 'Invalid option entered' else statement.
					value2 = 0;
				}

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
			case 3:
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

					std::cout << EL << "     Please enter the task number:" << EL;
					std::cout << EL << "     ";

					// Get the input from the user.
					std::cin >> input;
					int taskNumber;

					// Try catch statement for error checking.
					try
					{
						// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
						taskNumber = std::stoi(input);

					}
					catch (...)
					{
						// Exception. Assign -1 to follow the 'Invalid task number entered' else statement.
						taskNumber = -1;
					}

					// Valid value has been entered.
					if (taskNumber <= tasksVector.size() && taskNumber > 0)
					{
						// Clear the screen to display new information.
						system("CLS");

						// Output the details of the current project.
						std::cout << pm.printProjectDetails();

						// Output the chosen task.
						std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

						std::cout << EL << "     What type of time allocation would you like to add?" << EL;
						int num = 0;

						// A vector containing the different types time allocations obtained through the helper class.
						for (auto i : Helper::GetTaTypes())
						{
							std::cout << EL << "     '" << ++num << "' - " << i;
						}

						std::cout << EL << EL << "     If you no longer wish to add a TA then please enter '0'." << EL << EL;

						std::cout << EL << "     Please enter the TA type number:" << EL;
						std::cout << EL << "     ";

						// Get the input from the user.
						std::cin >> input;
						int TAType;

						// Try catch statement for error checking.
						try
						{
							// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
							TAType = std::stoi(input);

						}
						catch (...)
						{
							// Exception. Assign -1 to follow the 'Invalid TA number entered' else statement.
							TAType = -1;
						}

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
								TADuration;		

								// Try catch statement for error checking.
								try
								{
									// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
									TADuration = std::stoi(input);

								}
								catch (...)
								{
									// Exception. Assign -1 to follow the 'Invalid duration entered' else statement.
									TADuration = -1;
								}

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

								while (true)
								{

									std::cout << EL << "     Please enter the bug ID. Must be above 0" << EL;
									std::cout << EL << "     ";

									// Get the input from the user.
									std::cin >> input;
									bugID;

									// Try catch statement for error checking.
									try
									{
										// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
										bugID = std::stoi(input);

									}
									catch (...)
									{
										// Exception. Assign 0 to follow the 'Invalid option entered' else statement.
										bugID = 0;
									}

									if (bugID > 0)
									{
										break;
									}
									else
									{
										std::cout << EL << "     Invalid bug ID entered" << std::endl;
									}

								}

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
							// Research
							else if (TAType == 4)
							{
								std::string researchDescription;

								std::cout << EL << "     Please enter the description for the research" << EL;
								std::cout << EL << "     ";

								// Get the input from the user.
								std::getline(std::cin, researchDescription);

								// Add the research.
								pm.createResearch(TAStartDate, TAEndDate, researchDescription, tasksVector[taskNumber - 1]);								
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

						std::cout << EL << "Successfully added." << EL;

						while (true)
						{						
							std::cout << EL << "Would you like to save the project? y / n" << EL << EL;

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
			case 4:
			{
				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				std::string startDate, endDate, name, description;

				std::cout << EL << "Please enter a name for the task:" << EL << EL;

				std::cin.ignore();

				// Get the input from the user.
				std::getline(std::cin, name);

				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				std::cout << EL << "Please enter a description for the task:" << EL << EL;

				// Get the input from the user.
				std::getline(std::cin, description);

				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				while (true)
				{
					std::cout << EL << "Please enter the start date (DD/MM/YYYY HH:MM)" << EL << EL;

					// Get the input from the user.
					std::getline(std::cin, startDate);

					if (Helper::IsValidDateTime(startDate))
					{
						break;
					}
					else
					{
						std::cout << EL << "Invalid date entered" << std::endl;
					}
				}

				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				while (true)
				{
					std::cout << EL << "Please enter the end date (DD/MM/YYYY HH:MM)" << EL << EL;

					// Get the input from the user.
					std::getline(std::cin, endDate);

					if (Helper::IsValidDateTime(endDate))
					{
						break;
					}
					else
					{
						std::cout << EL << "Invalid date entered" << std::endl;
					}
				}

				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				std::cout << EL << "These details have been entered:" << EL;
				std::cout << "Name: " << name << EL
					<< "Description: " << description << EL
					<< "Start Date: " << startDate << EL
					<< "End Date: " << endDate << EL;

				std::cout << EL << "Are these details correct?" << EL << "Type 'y' for yes and 'n' for no" << EL << EL;

				std::cin >> input;

				if (input == "y")
				{
					// Clear the screen to display new information.
					system("CLS");

					// Output the details of the current project.
					std::cout << pm.printProjectDetails();

					// Add the task.
					pm.createTask(startDate, endDate, name, description);

					std::cout << EL << "Would you like to save the project?" << EL << "Type 'y' for yes and 'n' for no" << EL << EL;

					std::cin >> input;

					// Clear the screen to display new information.
					system("CLS");

					// Output the details of the current project.
					std::cout << pm.printProjectDetails();

					if (input == "y")
					{
						pm.save();
						std::cout << EL << "The task has been created and saved successfully" << EL;
					}
					else if (input == "n")
					{
						std::cout << EL << "The task has been created successfully" << EL;
					}
					else
					{
						std::cout << EL << "Invalid choice" << EL;
						std::cout << EL << "Press enter to choose again";
						std::cin.ignore();
						std::cin.get();
					}					
				}
				else if (input == "n")
				{
					// Clear the screen to display new information.
					system("CLS");

					// Output the details of the current project.
					std::cout << pm.printProjectDetails();

					std::cout << EL << "The task creation has been cancelled" << EL;
				}
				else
				{
					std::cout << EL << "Invalid choice" << EL;
					std::cout << EL << "Press enter to choose again";
					std::cin.ignore();
					std::cin.get();
				}

				break;
			}
			case 5:
			{
				createNewProject(pm);
				break;
			}
			case 9:
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
			case 8:
			{
				// Save any changes made changes.
				pm.save();
				
				// Clear the screen to display new information.
				system("CLS");

				// Output the details of the current project.
				std::cout << pm.printProjectDetails();

				while (true)
				{
					// Give the user an option to back out.
					std::cout << EL << "Are you sure you wish to delete the current project?" << EL << "Type 'y' for yes and 'n' for no" << EL << EL;

					std::cin >> input;

					if (input == "y")
					{
						// Clear the screen to display new information.
						system("CLS");

						pm.deleteCurrentProject();
						std::cout << EL << "The project has been successfully deleted" << EL;
						break;
					}
					else if (input == "n")
					{
						// Clear the screen to display new information.
						system("CLS");

						std::cout << EL << "The project has not been deleted" << EL;
						break;
					}
					else
					{
						std::cout << EL << "Invalid answer." << EL;
					}
				}
				
				// Save the changes to the text file.
				pm.save();

				// Choose a project.
				chooseProject(pm);
				break;
			}
			case 6:
			{
				while (true)
				{
					// Clear the screen to display new information.
					system("CLS");

					// Output the details of the current project.
					std::cout << pm.printProjectDetails();

					// Used to store a list of task names.
					std::vector<std::string> tasksVector = {};

					// Get all of the tasks in the project.
					std::cout << pm.printTasks(tasksVector);

					if (tasksVector.size() == 0)
					{
						break;
					}

					std::cout << EL << "     Which task would you like to delete a time allocation from?";
					std::cout << EL << "     If you no longer wish to delete a TA then please enter '0'." << EL;

					std::cout << EL << "     Please enter the task number:" << EL;
					std::cout << EL << "     ";

					// Get the input from the user.
					std::cin >> input;
					int taskNumber;

					// Try catch statement for error checking.
					try
					{
						// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
						taskNumber = std::stoi(input);

					}
					catch (...)
					{
						// Exception. Assign -1 to follow the 'Invalid task number entered' else statement.
						taskNumber = -1;
					}

					// Valid value has been entered.
					if (taskNumber <= tasksVector.size() && taskNumber > 0)
					{
						while (true)
						{
							// Clear the screen to display new information.
							system("CLS");

							// Output the details of the current project.
							std::cout << pm.printProjectDetails();

							// Output the chosen task.
							std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);

							int TACount = 0;

							// Print out the list of TAs for this task.
							std::cout << EL << pm.printTaskTAs(tasksVector[taskNumber - 1], TACount);

							if (TACount == 0)
							{
								std::cout << EL << "     There are no time allocations to delete" << EL;
								break;
							}

							std::cout << EL << "     Which time allocation would you like to delete?" << EL;							

							std::cout << EL << EL << "     If you no longer wish to delete a TA then please enter '0'." << EL;

							std::cout << EL << "     Please enter the TA number:" << EL;
							std::cout << EL << "     ";

							// Get the input from the user.
							std::cin >> input;
							int TANumber;

							// Try catch statement for error checking.
							try
							{
								// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
								TANumber = std::stoi(input);

							}
							catch (...)
							{
								// Exception. Assign -1 to follow the 'Invalid TA number entered' else statement.
								TANumber = -1;
							}

							// User wishes to cancel.
							if (TANumber == 0)
							{
								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();
								break;
							}
							// Valid value has been entered.
							else if (TANumber <= TACount && TANumber > 0)
							{								
								// Clear the screen to display new information.
								system("CLS");

								// Output the details of the current project.
								std::cout << pm.printProjectDetails();

								// Output the chosen task.
								std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);								
								
								while (true)
								{
									// Give the user an option to back out.
									std::cout << EL << "          Are you sure you wish to delete this time allocation?" << EL << "          Type 'y' for yes and 'n' for no" << EL;

									std::cout << pm.printTADetails(tasksVector[taskNumber - 1], TANumber);

									std::cout << EL << "          ";

									std::cin >> input;

									if (input == "y")
									{
										// Clear the screen to display new information.
										system("CLS");

										// Delete the TA
										pm.deleteTA(tasksVector[taskNumber - 1], TANumber);

										std::cout << EL << "The time allocation has been successfully deleted" << EL;
										pm.save();
										break;
									}
									else if (input == "n")
									{
										// Clear the screen to display new information.
										system("CLS");

										std::cout << EL << "The time allocation has not been deleted" << EL;
										break;
									}
									else
									{
										std::cout << EL << "          Invalid answer." << EL;
										std::cout << EL << "          Press enter to continue..." << EL;

										std::cin.ignore();
										std::cin.get();
									}
								}
								break;
							}
							else
							{
								std::cout << EL << "     Invalid TA number entered" << EL;
								std::cout << EL << "     Press enter to continue..." << EL;

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
			case 7:
			{
				while (true)
				{
					// Clear the screen to display new information.
					system("CLS");

					// Used to store a list of task names.
					std::vector<std::string> tasksVector = {};

					std::cout << pm.printProjectDetails();

					// Get all of the tasks in the project.
					std::cout << pm.printTasks(tasksVector);

					if (tasksVector.size() == 0)
					{
						break;
					}

					std::cout << EL << "     Which task would you like to delete?";
					std::cout << EL << "     If you no longer wish to delete a Task then please enter '0'." << EL;

					std::cout << EL << "     Please enter the task number:" << EL;
					std::cout << EL << "     ";

					// Get the input from the user.
					std::cin >> input;
					int taskNumber;

					// Try catch statement for error checking.
					try
					{
						// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
						taskNumber = std::stoi(input);

					}
					catch (...)
					{
						// Exception. Assign -1 to follow the 'Invalid task number entered' else statement.
						taskNumber = -1;
					}

					// Valid value has been entered.
					if (taskNumber <= tasksVector.size() && taskNumber > 0)
					{
						while (true)
						{
							// Clear the screen to display new information.
							system("CLS");

							std::cout << pm.printProjectDetails();

							// Give the user an option to back out.
							std::cout << EL << "     Are you sure you wish to delete this task?" << EL << "     Type 'y' for yes and 'n' for no" << EL;

							std::cout << pm.printTaskDetails(tasksVector[taskNumber - 1]);
							std::cout << EL << "     ";

							std::cin >> input;

							if (input == "y")
							{
								// Clear the screen to display new information.
								system("CLS");

								// Delete the task
								pm.deleteTask(tasksVector[taskNumber - 1]);

								std::cout << EL << "The task has been successfully deleted" << EL;
								pm.save();
								break;
							}
							else if (input == "n")
							{
								// Clear the screen to display new information.
								system("CLS");

								std::cout << EL << "The task has not been deleted" << EL;
								break;
							}
							else
							{
								std::cout << EL << "     Invalid answer." << EL;
								std::cout << EL << "     Press enter to continue..." << EL;

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

void createNewProject(ProjectManager& pm)
{
	void chooseProject(ProjectManager& pm);

	std::string input, startDate, deadLine, name, description;

	while (true)
	{
		std::cout << EL << "Please enter a name for the Project" << EL << EL;

		std::cin.ignore();

		// Get the input from the user.
		std::getline(std::cin, name);

		// Clear the screen to display new information.
		system("CLS");

		std::cout << EL << "Please enter a description for the project" << EL << EL;

		// Get the input from the user.
		std::getline(std::cin, description);

		// Clear the screen to display new information.
		system("CLS");

		while (true)
		{
			std::cout << EL << "Please enter a start date for the project (DD/MM/YYYY HH:MM)" << EL << EL;

			// Get the input from the user.
			std::getline(std::cin, startDate);

			if (Helper::IsValidDateTime(startDate))
			{
				break;
			}
			else
			{
				std::cout << EL << "Invalid date entered" << std::endl;
			}
		}

		// Clear the screen to display new information.
		system("CLS");

		while (true)
		{
			std::cout << EL << "Please enter a deadline date for the project (DD/MM/YYYY HH:MM)" << EL << EL;

			// Get the input from the user.
			std::getline(std::cin, deadLine);

			if (Helper::IsValidDateTime(deadLine))
			{
				break;
			}
			else
			{
				std::cout << EL << "Invalid date entered" << std::endl;
			}
		}

		bool answer = true;

		bool currentAnswer = answer;

		// Clear the screen to display new information.
		system("CLS");

		std::cout << EL << "These details have been entered:" << EL;
		std::cout << "Name: " << name << EL
			<< "Description: " << description << EL
			<< "Start Date: " << startDate << EL
			<< "Deadline: " << deadLine << EL;

		std::cout << EL << "Are these details correct?" << EL << "Type 'y' for yes and 'n' for no" << EL << EL;

		std::cin >> input;

		if (input == "y")
		{
			// Create project will set the project pointer to 1.
			pm.createProject(startDate, deadLine, name, description);
			pm.save();

			// Clear the screen to display new information.
			system("CLS");

			std::cout << EL << "The project has been created and saved successfully" << EL;

			chooseProject(pm);

			break;
		}
		else
		{
			// Clear the screen to display new information.
			system("CLS");

			std::cout << EL << "Would you like to enter the information again?" << EL << "Type 'y' for yes and 'n' for no" << EL;

			std::cin >> input;

			if (input != "y")
			{
				std::cout << EL << "The project creation has been cancelled" << EL;

				// Create project will set the project pointer to 1.				
				break;
			}

			// Clear the screen to display new information.
			system("CLS");
		}
	}
}

void chooseProject(ProjectManager& pm)
{
	// Print out all of the projects 
	std::cout << pm.printAllProjectDetails();	

	std::string input = "";

	while (true)
	{
		// If there are no projects then a new project must be created and added.
		if (pm.numberOfProjects() > 0)
		{
			std::cout << EL << "Which project would you like to use?" << EL;

			std::cout << EL << "Please enter the project number: " << EL << EL;

			// Get the input from the user.
			std::cin >> input;

			int projectNumber;

			// Try catch statement for error checking.
			try
			{
				// Assing the numeric value. If a numeric value can not be assigned then an exception will be thrown.
				projectNumber = std::stoi(input);

			}
			catch (...)
			{
				// Exception. Assign 0 to follow the 'Invalid Project number entered' else statement.
				projectNumber = 0;
			}

			// Valid value has been entered.
			if (projectNumber <= pm.numberOfProjects() && projectNumber > 0)
			{
				pm.setProjectPointer(projectNumber);
				break;
			}
			else
			{
				std::cout << EL << "Invalid Project number entered" << EL;
			}
		}
		else
		{
			while (pm.numberOfProjects() == 0)
			{
				std::cout << EL << "Please create a new project." << EL;

				createNewProject(pm);
			}
			break;
		}
	}
}