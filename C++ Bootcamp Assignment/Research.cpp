#include "Research.h"

Research::Research(std::string start, std::string end, std::string workDescription)
	: TimeAllocation(start, end), description(workDescription)
{
}

Research::~Research()
{
}

std::string Research::getDetails() const
{
	std::ostringstream oss;

	oss << "\n          Research\n"
		<< "          Description: " << description << EL
		<< "          Date: " << getStartDate() << EL
		<< "          Time taken: " << Helper::MinutesToTime(getDuration()) << EL;

	return oss.str();
}

std::string Research::save() const
{
	std::ostringstream oss;

	oss << "Research" << EL
		<< getStartDate() << EL
		<< getEndDate() << EL
		<< description << EL;

	return oss.str();
}
