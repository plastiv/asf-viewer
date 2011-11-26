#include "stdafx.h"
#include "AsfHeader.h"

namespace Asf {

void AsfHeader::addProperty(const std::string& propertyLine)
	// By default propertyLine pattern is PROPERTY_NAME Value
{
	std::tr1::smatch mathes; // matched strings go here
	if (std::tr1::regex_search(propertyLine, mathes, pattern))
	{
		values.insert(make_pair(mathes[1], mathes[2]));
	}
	else
	{
		// TODO : make an error here "bad header line format"
	}
}

void AsfHeader::print(std::ostream& outputStream) const
	// write all properties back
{
	for (std::map <std::string, std::string>::const_iterator p = values.begin(); p!= values.end(); ++p)
	{
		outputStream << p->first << ' ' << p->second << std::endl;
	}

	outputStream << std::endl; // end of header
}

} // end of namespace
