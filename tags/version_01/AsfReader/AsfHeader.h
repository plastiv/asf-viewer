#pragma once
#include "AsfError.h"
#include <string>
#include <regex>
#include <map>

namespace Asf {

class AsfHeader
	// Saves pairs of AsfFile properties and its values
{
public:
	AsfHeader(void) : pattern("([A-Z_]+) (.+)") {}
	void addProperty(const std::string& propertyLine);
	std::string operator[](const std::string& parametr) const { return values.at(parametr); }
	void print(std::ostream& outputStream) const;
	~AsfHeader(void) {}
private:
	const std::tr1::regex pattern;
	std::map<std::string, std::string> values;
};

} // end of namespace