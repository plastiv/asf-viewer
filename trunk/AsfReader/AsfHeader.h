#pragma once
#include <vector>
#include <string>
#include <regex>
#include <map>

namespace Asf {

typedef std::vector<std::string>::const_iterator LineIterator;

class AsfHeader
	// points to the first and the last lines of AsfFile that are header information
{
public:
	AsfHeader(void) : pattern("([A-Z_]+) (\.+)") {}
	AsfHeader(LineIterator firstP, LineIterator lastP);
	void addProperty(const std::string& propertyLine);

	std::string operator[](const std::string& parametr) const { return values.at(parametr); }
	~AsfHeader(void){}
private:
	LineIterator first;
	LineIterator last;

	std::tr1::regex pattern;
	std::map <std::string, std::string> values;
};

}
