#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include "AsfHeader.h"

namespace Asf {

typedef std::shared_ptr<std::vector<unsigned char>> RowPtr;
typedef std::vector<RowPtr>::const_iterator RowPtrIterator;

class AsfFrame
	// a frame points to the first and the last lines of AsfFile as a raw source of data
	// and also store a converted values
	// TODO : separate classes, that used for different behavior
{
public:
	AsfFrame(void) : number_(0), timeStamp(0), pixels() {}
	void addHeaderLine(const std::string& headerLine);
	void addPixelsLine(const std::string& pixelsLine);
	void print(std::ostream& outputStream) const;
	size_t rows() const { return pixels.size(); }
	size_t cols() const { return pixels.at(0)->size(); }
	size_t number() const { return number_; }
	RowPtrIterator begin() const { return pixels.begin(); }
	RowPtrIterator end() const { return pixels.end(); }
	~AsfFrame(void);
private:
	// TODO : save rows & cols to save consistant reallocation
	std::vector<RowPtr> pixels;
	size_t number_;
	size_t timeStamp; 
};

} // end of namespace
