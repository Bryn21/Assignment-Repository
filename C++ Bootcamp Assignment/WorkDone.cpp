#include "WorkDone.h"

WorkDone::WorkDone(std::string start, std::string end, std::string workDescription)
	: TimeAllocation(start, end), description(workDescription)
{
}

WorkDone::~WorkDone()
{
}

std::string WorkDone::getDetails()
{
	std::ostringstream oss;

	oss << "\n          Work Done\n"
		<< "          Description: " << description << '\n'
		<< "          Date: " << getStartDate() << '\n'
		<< "          Time taken: " << getDuration() << " Minutes\n";

	return oss.str();
}

std::string WorkDone::save()
{
	std::ostringstream oss;

	oss << "WorkDone" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< description << EL;

	return oss.str();
}
