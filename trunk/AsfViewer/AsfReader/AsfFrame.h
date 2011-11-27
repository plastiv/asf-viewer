#pragma once
#include "AsfError.h"
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <iostream> // For clog only

namespace Asf {

typedef std::shared_ptr<std::vector<unsigned char>> RowPtr;
typedef std::vector<RowPtr>::const_iterator RowPtrIterator;

class AsfFrame
	// store matrix of pixels brightness values
{
public:
	AsfFrame(void) : number_(0), timeStamp(0), cols_(0), pixels() {}
	AsfFrame(size_t rows, size_t cols);
	void addHeaderLine(const std::string& headerLine);
	void addPixelsLine(const std::string& pixelsLine);
	void print(std::ostream& outputStream) const;
	size_t rows() const { return pixels.size(); }
	size_t cols() const { return pixels.at(0)->size(); }
	size_t number() const { return number_; }
	RowPtrIterator begin() const { return pixels.begin(); }
	RowPtrIterator end() const { return pixels.end(); }
	~AsfFrame(void) {}
private:
	std::vector<RowPtr> pixels;
	size_t number_;
	size_t timeStamp; 
	size_t cols_; // For vector.reserve() to save possible realocations
};

} // end of namespace
