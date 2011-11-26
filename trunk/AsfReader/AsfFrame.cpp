#include "stdafx.h"
#include "AsfFrame.h"

namespace Asf {

AsfFrame::AsfFrame(LineIterator firstP, LineIterator lastP):first(firstP),last(lastP)
{
	std::tr1::regex frameHeader("Frame\\s(\\d+)(,\\stimestamp\\s)?(\\d+)?$"); // "Frame 1, timestamp 12345" pattern

	std::tr1::smatch mathes; // matched strings go here

	// get frame number and optional timestamp number
	if (std::tr1::regex_search(*first, mathes, frameHeader)) {
		number = atoi(mathes[1].str().c_str()); // save frame number
		if (1<mathes.size() && mathes[3].matched) {
			timeStamp = atoi(mathes[3].str().c_str()); // save timestamp if exist
		}
	} else {
		// TODO : send error wrong frame header format
	}

	int currentRow = -1;
	// input all values from string to vector<vector<uchar>>
	for (LineIterator p = first+1; p!= last; ++p) {
		pixels.push_back(std::vector<unsigned char>());
		++currentRow;
		std::stringstream ss(*p);
		int i;
		while (ss >> i)
		{
			pixels[currentRow].push_back(i);
			if(ss.peek() == ',')
				ss.ignore();
			else if (ss.peek() == 13) // TODO: not necessary check, include in debug inly
				ss.ignore();
		}
	}
}

AsfFrame::~AsfFrame(void) {}

}