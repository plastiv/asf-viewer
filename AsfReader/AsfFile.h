#pragma once
#include "AsfFrame.h"
#include "AsfHeader.h"
#include "AsfError.h"
#include <string>
#include <vector>
#include <iostream>

namespace Asf {

typedef std::shared_ptr<AsfFrame> FramePtr;
typedef std::vector<FramePtr>::const_iterator FramePtrIterator;

class AsfFile
	// represent .asf file state in memory
{
public:
	AsfFile(std::istream& inputStream); // read istream into lines
	FramePtrIterator begin() const { return frames.begin(); }
	FramePtrIterator end() const { return frames.end(); }
	std::string getPropertyByName (const std::string& propertyName) const { return asfHeader[propertyName]; }
	void print(std::ostream & outputStream) const;
	bool isCorrect() const;
	~AsfFile(void) {}
private:
	void readHeader(std::istream& inputStream);
	void readFrames(std::istream& inputStream);
	std::vector<FramePtr> frames; // frames in order
	AsfHeader asfHeader;
};

} // end of namespace
