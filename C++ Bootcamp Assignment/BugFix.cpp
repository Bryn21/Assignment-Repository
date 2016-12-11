#include "BugFix.h"

BugFix::BugFix(std::string start, std::string end, int bugID, std::string bugDescription)
	: TimeAllocation(start, end), ID(bugID), description(bugDescription)
{
}

BugFix::~BugFix()
{
}

std::string BugFix::getDetails() const
{
	std::ostringstream oss;

	oss << "\n          Bug Fix\n"
		<< "          Bug ID: " << ID << EL
		<< "          Bug Description: " << description << EL
		<< "          Date: " << getStartDate() << EL
		<< "          Time taken: " << Helper::MinutesToTime(getDuration()) << EL;

	return oss.str();
}

std::string BugFix::save() const
{
	std::ostringstream oss;

	oss << "BugFix" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< ID << EL
		<< description << EL;

	return oss.str();
}