#include "BugFix.h"

BugFix::BugFix(std::string start, std::string end, int bugID, std::string bugDescription)
	: TimeAllocation(start, end), ID(bugID), description(bugDescription)
{
}

BugFix::~BugFix()
{
}

std::string BugFix::getDetails()
{
	std::ostringstream oss;

	oss << "\n          Bug Fix\n"
		<< "          Bug ID: " << ID << '\n'
		<< "          Bug Description: " << description << '\n'
		<< "          Date: " << getStartDate() << '\n'
		<< "          Time taken: " << getDuration() << " Minutes\n";

	return oss.str();
}

std::string BugFix::save()
{
	std::ostringstream oss;

	oss << "BugFix" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< ID << EL
		<< description << EL;

	return oss.str();
}