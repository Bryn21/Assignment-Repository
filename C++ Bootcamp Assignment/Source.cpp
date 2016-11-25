#include "MainHeaderFiles.h"
#include "ProjectManager.h"

int main()
{
	std::cout << "C++ bootcamp assignment" << EL;

	ProjectManager pm;

	pm.createProject("11/12/2016 12:15", "11/12/2016 13:15", "Project 1", "Description of the project");

	pm.createTask("11/12/2016 12:15", "11/12/2016 13:15", "Task 1", "Description of the task");

	pm.createMeeting("11/12/2016 12:15", "11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell", "Task 1");

	//Project project("11/12/2016 12:15", "11/12/2016 13:15", "Project 1", "Description of the project");

	//Task task("11/12/2016 12:15", "11/12/2016 13:15", "Task 1", "Description of the task");

	//project.addTask(task);

	//// TODO - Scope problem with the unique pointers.
	//auto meeting = std::make_unique<Meeting>("11/12/2016 12:15", "11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell");

	//project.addTimeAllocationToTask(task, meeting.get());

	pm.save();

	//auto workDone = std::make_unique<WorkDone>("11/12/2016 12:15", "11/12/2016 13:15", "Did some work on the assignment");
	//auto bugFix = std::make_unique<BugFix>("11/12/2016 12:15", "11/12/2016 13:15", 1, "Fixed a bug with a DateTime problem");

	// Meeting meeting = ("11/12/2016 12:15","11/12/2016 13:15", "The Gym", "Alan Davis, Joe Bignell");
	// WorkDone workDone("11/12/2016 12:15", "11/12/2016 13:15", "Did some work on the assignment");
	// BugFix bugFix("11/12/2016 12:15", "11/12/2016 13:15", 1, "Fixed a bug with a DateTime problem");

	
	//project.addTimeAllocationToTask(task, workDone.get());
	//project.addTimeAllocationToTask(task, bugFix.get());

	ProjectManager pm2;

	pm2.load();

	std::cin.get();
}