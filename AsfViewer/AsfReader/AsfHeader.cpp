#include "stdafx.h"
#include "AsfHeader.h"

namespace Asf {

AsfHeader::AsfHeader(std::istream& inputStream) : pattern("([A-Z_]+) (.+)")
	// read header part
	// Supposed to be from the begging of a file until first blank line
	// exact size of header may be varied from file to file
{
	std::string currentLine; // read buffer

	getline(inputStream, currentLine);
	while (currentLine.size() > 1) { // end of header 
		// separator is blank line with zero size
		// or char 13 symbol
		addProperty(currentLine);
		getline(inputStream, currentLine);
	}
}

void AsfHeader::addProperty(const std::string& propertyLine)
	// By default propertyLine pattern is PROPERTY_NAME Value
{
	std::tr1::smatch mathes; // matched strings go here
	if (std::tr1::regex_search(propertyLine, mathes, pattern))
		values.insert(make_pair(mathes[1], mathes[2]));
	else
		Asf::error("Header line has a bad format ", propertyLine);
}

void AsfHeader::print(std::ostream& outputStream) const
	// write all properties back
{
	for (std::map<std::string, std::string>::const_iterator p = values.begin();
		p!= values.end(); ++p) {
		outputStream << p->first << ' ' << p->second << std::endl;
	}

	outputStream << std::endl; // end of header
}

} // end of namespace
