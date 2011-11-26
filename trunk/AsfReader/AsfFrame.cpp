#include "stdafx.h"
#include "AsfFrame.h"
#include <iostream> // TODO : For clog only

namespace Asf {

void AsfFrame::addHeaderLine(const std::string& headerLine)
{
	//std::clog << "AsfFrame addHeaderLine " << std::endl;

	std::tr1::regex headerPattern("Frame[[:space:]](\\d+)(,[[:space:]]timestamp[[:space:]])?(\\d+)?$"); // "Frame 1, timestamp 12345" pattern

	std::tr1::smatch mathes; // matched strings go here

	// get frame number and optional timestamp number
	if (std::tr1::regex_search(headerLine, mathes, headerPattern)) {
		number_ = atoi(mathes[1].str().c_str()); // save frame number
		if (1<mathes.size() && mathes[3].matched) {
			timeStamp = atoi(mathes[3].str().c_str()); // save timestamp if exist
		}
	} else {
		// TODO : send error wrong frame header format
	}
}

void AsfFrame::addPixelsLine(const std::string& pixelsLine)
{
	//std::clog << "AsfFrame addPixelsLine " << std::endl;

	RowPtr pixelRow(new std::vector<unsigned char>());
	pixels.push_back(pixelRow);
	RowPtrIterator currentRow = pixels.end() - 1;

	std::stringstream ss(pixelsLine);
	int i;
	while (ss >> i)
	{
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
		outputStream << "Frame " << number_ << ',' << " timestamp " << timeStamp << std::endl;

	for (RowPtrIterator it = pixels.begin(); it != pixels.end(); ++it) {
		for (std::vector<unsigned char>::const_iterator ch = (*it)->begin();
			ch !=(*it)->end() - 1; ++ch)
		outputStream << (int)*ch << ',';

		outputStream << (int)*((*it)->end() - 1) << std::endl; // last digit in row doesnt have separator after itself
	}

	outputStream << std::endl;
}

AsfFrame::~AsfFrame(void) {}

}