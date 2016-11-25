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

	oss << "\nWork Done\n"
		<< "Description: " << description << '\n'
		<< "Date: " << getStartDate() << '\n'
		<< "Time taken: " << getDuration() << " Minutes\n";

	return oss.str();
}
