#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include "AsfHeader.h"

namespace Asf {
typedef std::vector<std::vector<unsigned char>>::const_iterator RowIterator;

class AsfFrame
	// a frame points to the first and the last lines of AsfFile as a raw source of data
	// and also store a converted values
	// TODO : separate classes, that used for different behavior
{
public:
	AsfFrame(LineIterator firstP, LineIterator lastP);
	RowIterator begin() const {return pixels.begin();}
	RowIterator end() const {return pixels.end();}
	std::vector<std::vector<unsigned char>> pixels; // TODO : temp decision to open pixels
	~AsfFrame(void);
private:
	LineIterator first;
	LineIterator last;

	size_t number;
	size_t timeStamp; 
};

} // end of namespace
