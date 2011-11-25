#pragma once
#include "AsfLibrary/AsfFile.h"
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <iostream>
#include <fstream>

namespace Asf {

	// no classes, just functions in AsfUtilities.cpp
	void printError(const char* why, const char* what="");
	std::tr1::shared_ptr<AsfFile> createFromFile(const char * fileName);
	std::tr1::shared_ptr<AsfFile> createFromGzipFile(const char * fileName);
	void writeToFile (char * fileName, std::tr1::shared_ptr<AsfFile> &fileToWrite);
	void writeToGzipFile (char * fileName, std::tr1::shared_ptr<AsfFile> &fileToWrite);
}
