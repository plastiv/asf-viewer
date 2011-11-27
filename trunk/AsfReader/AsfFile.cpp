#include "stdafx.h"
#include "AsfFile.h"

namespace Asf {

AsfFile::AsfFile( std::istream& inputStream )
	// read string by string from inputStream
	// find the frames and compose them in "frames"
	// assume every frame is separated by blank "" line
{
	//std::clog << "AsfFile constructor start " << std::endl;

	readHeader(inputStream);

	//a little bit analyze to save vectors reallocation
	size_t startFrame = atoi(asfHeader["START_FRAME"].c_str());
	size_t endFrame = atoi(asfHeader["END_FRAME"].c_str());
	size_t frameCount = endFrame - startFrame + 1;
	frames.reserve(frameCount);

	readFrames(inputStream);

	if(!isCorrect()) Asf::error("Cannot read file correctly. Bad data");
}

void AsfFile::readHeader( std::istream& inputStream )
	// read header part
	// Supposed to be from the begging of a file until first blank line
	// exact size of header may be varied from file to file
{
	std::string currentLine; // read buffer

	getline(inputStream, currentLine);
	while (currentLine.size() > 1){ // end of header 
		// separator is blank line with zero size
		// or char 13 symbol
		asfHeader.addProperty(currentLine);
		getline(inputStream, currentLine);
	}
}

void AsfFile::readFrames( std::istream& inputStream )
	// read frames part
{
	size_t rows = atoi(asfHeader["ROWS"].c_str()); // for vector.reserve()
	size_t cols = atoi(asfHeader["COLS"].c_str());

	std::string currentLine; // read buffer

	while (getline(inputStream, currentLine) && currentLine.size() > 3) {
		// while str left or found @@ - EOF
		std::shared_ptr<AsfFrame> newFrame(new Asf::AsfFrame(rows, cols));
		newFrame->addHeaderLine(currentLine);

		getline(inputStream, currentLine);
		while (currentLine.size() > 3){ // end of frame 
			// separator is blank line with zero size
			// or char 13 symbol
			// or @@
			newFrame->addPixelsLine(currentLine);
			getline(inputStream, currentLine);
		}
		
		frames.push_back(newFrame);
	}
}

void AsfFile::print( std::ostream & outputStream ) const
{
	//std::clog << "AsfFile print start " << std::endl;

	asfHeader.print(outputStream);

	for (FramePtrIterator it = frames.begin(); it!= frames.end(); ++it)
	{
		(*it)->print(outputStream);
	}

	//outputStream << "@@" << std::endl; //EOF in case you need it
}

bool AsfFile::isCorrect() const
	// Check if header information equal actual
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
	else if (frames.at(frames.size()-1)->rows() != rows)
		return false;
	else if (frames.at(frames.size()-1)->cols() != cols)
		return false;
	else if (frames.at(0)->number() != startFrame)
		return false;
	else if ((*(frames.end() - 1))->number() != endFrame)
		return false;
	else 
		return true;
}

} // end of namespace
