#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "AsfFrame.h"
#include "AsfHeader.h"

namespace Asf {

typedef std::vector<AsfFrame>::const_iterator FrameIterator;

class AsfFile
	// Asf File holds all the lines from a file
	// and simplifies access to frames
{
public:
	AsfFile(std::istream& inputStream); // read istream into lines
	FrameIterator begin() const { return frames.begin(); }
	FrameIterator end() const { return frames.end(); }
	void print(std::ostream & outputStream) const;
	std::string& getPropertyByName (const std::string& propertyName) const { return asfHeader[propertyName]; }
	bool isCorrect() const;
	~AsfFile(void);
private:
	const std::string FRAME_SEPARATOR;
	std::vector<std::string> lines; //the file lines in order
	std::vector<AsfFrame> frames; // frames in order
	AsfHeader asfHeader;
};

} // end of namespace