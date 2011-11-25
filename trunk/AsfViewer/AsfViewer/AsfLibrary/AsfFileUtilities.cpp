#include "AsfLibrary/AsfFileUtilities.h"

namespace Asf {

void printError(const char* why, const char* what)
	// Error message function for Console Projects
{
	std::cerr << why << ' ' << what << std::endl;
	std::cout << "The program has terminated!" << std::endl;
	exit(1);
}

std::tr1::shared_ptr<AsfFile> createFromFile(const char * fileName)
	// open file named fileName
{
	std::clog << "Create AsfFile from file " << fileName << std::endl;
	std::ifstream inputFile(fileName); // open the file
	if (!inputFile)
		Asf::printError("can not open file", fileName);

	return std::tr1::shared_ptr<AsfFile>(new AsfFile(inputFile));
}

std::tr1::shared_ptr<AsfFile> createFromGzipFile(const char * fileName)
	// open GZip file named fileName
{
	std::clog << "Create AsfFile from GZip file " << fileName << std::endl;
	std::ifstream inputGzipFile(fileName, std::ios_base::in | std::ios_base::binary); // open the file
	if (!inputGzipFile)
		printError("can not open file", fileName);

	boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
	in.push(boost::iostreams::gzip_decompressor());
	in.push(inputGzipFile);

	std::istream out(&in);
	std::tr1::shared_ptr<AsfFile> pasf(new AsfFile(out));
	return pasf;
}

void writeToFile (char * fileName, std::tr1::shared_ptr<AsfFile> &fileToWrite)
	// Save AsfFile state to fileName file
{
	std::clog << "Write AsfFile to file " << fileName << std::endl;
	std::ofstream outputFile(fileName, std::ios_base::out | std::ios_base::trunc);	//open output file stream
	if (!outputFile) printError("cannot open output file", fileName);

	fileToWrite->print(outputFile);
}

void writeToGzipFile (char * fileName, std::tr1::shared_ptr<AsfFile> &fileToWrite)
	// Save AsfFile state to fileName GZip file
{
	std::clog << "Write AsfFile to GZip file " << fileName << std::endl;
	std::ofstream outputGzipFile(fileName, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);	//open output file stream
	if (!outputGzipFile) printError("cannot open output file", fileName);

	boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
	out.push(boost::iostreams::gzip_compressor());
	out.push(outputGzipFile);

	std::stringstream ss;
	fileToWrite->print(ss);

	boost::iostreams::copy(ss, out);
}

} // end namespace Asf