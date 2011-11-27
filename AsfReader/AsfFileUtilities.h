#pragma once
#include "AsfFile.h"
#include "AsfError.h"
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <iostream>
#include <fstream>

namespace Asf {

// no classes, just functions for read/write file
// for better incapsulation of AsfFile class
std::tr1::shared_ptr<AsfFile> createFromFile(const char* fileName);
std::tr1::shared_ptr<AsfFile> createFromGzipFile(const char* fileName);
void writeToFile(const char* fileName, const std::tr1::shared_ptr<AsfFile>& fileToWrite);
void writeToGzipFile(const char* fileName, const std::tr1::shared_ptr<AsfFile>& fileToWrite);
}
