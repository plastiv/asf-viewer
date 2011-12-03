#include "stdafx.h"
#include "AsfFrame.h"

namespace Asf {

AsfFrame::AsfFrame(std::istream& inputStream, size_t rows, size_t cols) : number_(0), timeStamp(0), cols_(cols), pixels(), isCorrect_(false)
{
	std::string currentLine; // read buffer
	getline(inputStream, currentLine);

	if (currentLine.size() < 3) // find symbol EOF
	// could be quicker than (currentLine == "" || currentLine == "@@")
		return; // dont make frame
	addHeaderLine(currentLine);

	pixels.reserve(rows);

	getline(inputStream, currentLine);
	while (currentLine.size() > 3){ // end of frame 
		// separator is blank line with zero size
		// or char 13 symbol
		// or @@
		addPixelsLine(currentLine);
		getline(inputStream, currentLine);
	}

	if (pixels.size() == rows)
		if (pixels.at(pixels.size() - 1)->size() == cols)
			isCorrect_ = true;
}

void AsfFrame::addHeaderLine(const std::string& headerLine)
	// parse frame header line
{
	//std::clog << "AsfFrame addHeaderLine " << std::endl;
	// "Frame 1, timestamp 12345" pattern
	std::tr1::regex headerPattern("Frame[[:space:]](\\d+)(,[[:space:]]timestamp[[:space:]])?(\\d+)?");

	std::tr1::smatch mathes; // matched strings go here

	// get frame number and optional timestamp number
	if (std::tr1::regex_search(headerLine, mathes, headerPattern)) {
		number_ = atoi(mathes[1].str().c_str()); // save frame number
		if (1<mathes.size() && mathes[3].matched) {
			timeStamp = atoi(mathes[3].str().c_str()); // save timestamp if exist
		}
	} else
		Asf::error("Frame header line has a bad format ", headerLine);
}

void AsfFrame::addPixelsLine(const std::string& pixelsLine)
	// parse frame pixel line
{
	//std::clog << "AsfFrame addPixelsLine " << std::endl;

	RowPtr pixelRow(new std::vector<unsigned char>());
	pixelRow->reserve(cols_);
	pixels.push_back(pixelRow);
	RowPtrIterator currentRow = pixels.end() - 1;

	std::stringstream ss(pixelsLine);
	int i;
	while (ss >> i) {
		(*currentRow)->push_back(i);
		if(ss.peek() == ',')
			ss.ignore();
	}
}

void AsfFrame::print(std::ostream& outputStream) const
	// write frame back
{
	//std::clog << "AsfFrame " << number_ << " print " << std::endl;

	if (timeStamp == 0)
		outputStream << "Frame " << number_ << std::endl;
	else
		outputStream << "Frame " << number_ << ", timestamp " << timeStamp << std::endl;

	for (RowPtrIterator it = pixels.begin(); it != pixels.end(); ++it) {
		for (std::vector<unsigned char>::const_iterator ch = (*it)->begin();
			ch !=(*it)->end() - 1; ++ch)
			outputStream << (int)*ch << ',';

		outputStream << (int)*((*it)->end() - 1) << std::endl; // last digit in row doesnt have separator after itself
	}

	outputStream << std::endl;
}

} // end of namespace
