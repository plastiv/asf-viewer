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
	AsfHeader(void) {}
	AsfHeader(LineIterator firstP, LineIterator lastP);
	LineIterator begin() const {return first;}
	LineIterator end() const {return last;}
	std::string& operator[](const std::string& parametr);
	~AsfHeader(void){}
private:
	LineIterator first;
	LineIterator last;
	std::map <std::string, std::string> values;
};

}
