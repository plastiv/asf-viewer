#include "stdafx.h"
#include "AsfFile.h"

namespace Asf {

AsfFile::AsfFile( std::istream& inputStream ) : asfHeader(inputStream)
	// read string by string from inputStream
	// find the frames and compose them in "frames"
	// assume every frame is separated by blank "" line
{
	//std::clog << "AsfFile constructor start " << std::endl;

	//a little bit analyze to save vectors reallocation
	size_t startFrame = atoi(asfHeader["START_FRAME"].c_str());
	size_t endFrame = atoi(asfHeader["END_FRAME"].c_str());
	size_t frameCount = endFrame - startFrame + 1;
	frames.reserve(frameCount);

	readAllFrames(inputStream);

	if(!isCorrect()) Asf::error("Cannot read file correctly. Bad data");
}

void AsfFile::readAllFrames( std::istream& inputStream )
	// read frames part
{
	size_t rows = atoi(asfHeader["ROWS"].c_str()); // for vector.reserve()
	size_t cols = atoi(asfHeader["COLS"].c_str());

	bool isMoreFrames = true;
	while (isMoreFrames) {
		// while str left or found @@ - EOF
		std::shared_ptr<AsfFrame> newFrame(new Asf::AsfFrame(inputStream, rows, cols));
		if (newFrame->isCorrect())
			frames.push_back(newFrame);
		else
			isMoreFrames = false;
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
