#include "stdafx.h"
#include "AsfFile.h"

namespace Asf {

const std::string AsfFile::FRAME_SEPARATOR = "";

AsfFile::AsfFile( std::istream& inputStream )
	// read the lines from inputStream to "lines"
	// find the frames in the lines and compose them in "frames"
	// assume every message is separated by blank "" line
{
	std::string currentLine;
	while (getline(inputStream, currentLine))
		lines.push_back(currentLine); // build the vector of lines

	//check if last string is a @@
	if (*(lines.end() - 1) == "@@")
		*(lines.end() - 1) = ""; // it makes more clear for algorithm; no need special fo EOF

	LineIterator firstFrameLine;

	// find Header lines. Supposed to be from begging of the file until first Frame
	// exact size of header may be varied from file to file
	for (LineIterator p = lines.begin(); p!= lines.end(); ++p)
	{
		if (*p == FRAME_SEPARATOR || (*p).size() == 1){ // end of Header  // TODO : Very bad constants! try to handle situation, when str is from one carriage return symbol 13
			asfHeader = AsfHeader(lines.begin(), p);
			firstFrameLine = p + 1; // done with header, start frames part
			break;
		}
		else 
			asfHeader.addProperty(*p);
	}

	// build vector of frames
	for (LineIterator p = firstFrameLine; p!= lines.end(); ++p)
	{
		if (*p == FRAME_SEPARATOR || p->at(0) == 13){ // find end of frame
			frames.push_back(AsfFrame(firstFrameLine, p));
			firstFrameLine = p + 1; // skip not interesting blank separator line
		}
	}
}

AsfFile::~AsfFile(void) {}

void AsfFile::print( std::ostream & outputStream )
{
	// write back lines to ostream (TODO : correct only for Read Only Mode!)
	for (LineIterator p = lines.begin(); p!= lines.end(); ++p)
	{
		outputStream << *p << std::endl;
	}
}

bool AsfFile::isCorrect()
	// Check is header information equal actual
{
	int rows = atoi(asfHeader["ROWS"].c_str());
	int cols = atoi(asfHeader["COLS"].c_str());

	int startFrame = atoi(asfHeader["START_FRAME"].c_str());
	int endFrame = atoi(asfHeader["END_FRAME"].c_str());
	int frameCount = endFrame - startFrame + 1;

	if (frames.size() != frameCount)
		return false;
	else if (frames[0].pixels.size() != rows)
		return false;
	else if (frames[0].pixels[0].size() != cols)
		return false;
	else
		return true;
}

std::string& AsfFile::getPropertyByName(const std::string& propertyName)
{
	return asfHeader[propertyName];
}

} // end of namespace
