#include "stdafx.h"
#include "AsfFileUtilities.h"

namespace Asf {

std::tr1::shared_ptr<AsfFile> createFromFile(const char* fileName)
	// open file named fileName
{
	//std::clog << "Create AsfFile from file " << fileName << std::endl;
	std::ifstream inputFile(fileName);
	if (!inputFile) Asf::error("Can not open file ", fileName);

	std::tr1::shared_ptr<AsfFile> ptrAsfFile(new AsfFile(inputFile));
	return ptrAsfFile;
}

std::tr1::shared_ptr<AsfFile> createFromGzipFile(const char* fileName)
	// open GZip file named fileName
{
	//std::clog << "Create AsfFile from GZip file " << fileName << std::endl;
	std::ifstream inputGzipFile(fileName, std::ios_base::in | std::ios_base::binary);
	if (!inputGzipFile) Asf::error("Can not open file", fileName);

	boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
	in.push(boost::iostreams::gzip_decompressor());
	in.push(inputGzipFile);

	std::istream out(&in);
	std::tr1::shared_ptr<AsfFile> ptrAsfFile(new AsfFile(out));
	return ptrAsfFile;
}

void writeToFile(const char* fileName, const std::tr1::shared_ptr<AsfFile>& fileToWrite)
	// Save AsfFile state to fileName file
{
	//std::clog << "Write AsfFile to file " << fileName << std::endl;
	std::ofstream outputFile(fileName, std::ios_base::out | std::ios_base::trunc); // rewrite file
	if (!outputFile) Asf::error("Can not open file to save ", fileName);

	fileToWrite->print(outputFile);
}

void writeToGzipFile(const char* fileName, const std::tr1::shared_ptr<AsfFile>& fileToWrite)
	// Save AsfFile state to fileName GZip file
{
	//std::clog << "Write AsfFile to GZip file " << fileName << std::endl;
	std::ofstream outputGzipFile(fileName, std::ios_base::out | std::ios_base::trunc |
								 std::ios_base::binary);	//rewrite binary file
	if (!outputGzipFile) Asf::error("Can not open file to save ", fileName);

	boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
	out.push(boost::iostreams::gzip_compressor());
	out.push(outputGzipFile);
	std::stringstream ss;
	fileToWrite->print(ss);

	boost::iostreams::copy(ss, out);
}

} // end of namespace
