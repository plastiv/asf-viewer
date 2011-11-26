#include "stdafx.h"
#include "AsfFile.h"

namespace Asf {

AsfFile::AsfFile( std::istream& inputStream ) : FRAME_SEPARATOR("")
	// read string by string from inputStream
	// find the frames and compose them in "frames"
	// assume every frame is separated by blank "" line
{
	std::clog << "AsfFile constructor start " << std::endl;

	std::string currentLine; // read buffer

	// read header part
	// Supposed to be from the begging of a file until first blank line
	// exact size of header may be varied from file to file
	getline(inputStream, currentLine);
	while (currentLine.size() > 1){ // end of header 
		// separator is blank line with zero size
		// or char 13 symbol
		asfHeader.addProperty(currentLine);
		getline(inputStream, currentLine);
	}

	// read frames part
	while (getline(inputStream, currentLine) && currentLine.size() != 2) {
		// while str left or @@ - EOF
		std::shared_ptr<AsfFrame> newFrame(new Asf::AsfFrame());
		newFrame->addHeaderLine(currentLine);

		getline(inputStream, currentLine);
		while (currentLine.size() > 2){ // end of frame 
			// separator is blank line with zero size
			// or char 13 symbol
			newFrame->addPixelsLine(currentLine);
			getline(inputStream, currentLine);
		}
		
		frames.push_back(newFrame);
	}
}

AsfFile::~AsfFile(void) {}

void AsfFile::print( std::ostream & outputStream ) const
{
	std::clog << "AsfFile print start " << std::endl;

	asfHeader.print(outputStream);

	for (FramePtrIterator it = frames.begin(); it!= frames.end(); ++it)
	{
		(*it)->print(outputStream);
	}

	outputStream << "@@" << std::endl;
}

bool AsfFile::isCorrect() const
	// Check is header information equal actual
{
	int rows = atoi(asfHeader["ROWS"].c_str());
	int cols = atoi(asfHeader["COLS"].c_str());

	int startFrame = atoi(asfHeader["START_FRAME"].c_str());
	int endFrame = atoi(asfHeader["END_FRAME"].c_str());
	int frameCount = endFrame - startFrame + 1;

	if (frames.size() != frameCount)
		return false;
	else if (frames.at(0)->rows() != rows)
		return false;
	else if (frames.at(0)->cols() != cols)
		return false;
	else if (frames.at(0)->number() != startFrame)
		return false;
	else if ((*(frames.end() - 1))->number() != endFrame)
		return false;
	else 
		return true;
}

} // end of namespace
