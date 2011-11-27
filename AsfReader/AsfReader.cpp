// AsfReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AsfFile.h"
#include "AsfFileUtilities.h"
#include <time.h>

enum TestMode {
	ReadFileWriteFile,
	ReadFileWriteGzip,
	ReadGzipWriteFile,
	ReadGzipWriteGzip,
};

void testFile(const char* fileName, const char* saveFileName, TestMode mode)
{
	// Read file
	std::cout << "Read file " << fileName << std::endl;
	clock_t clockBegin, clockEnd;
	{
	clockBegin = clock();
	std::tr1::shared_ptr<Asf::AsfFile> asfFile;
	if (mode == ReadFileWriteFile || mode == ReadFileWriteGzip)
		asfFile = Asf::createFromFile(fileName);
	else
		asfFile = Asf::createFromGzipFile(fileName);
	clockEnd = clock();

	std::cout << "File read correctly: " << asfFile->isCorrect() << std::endl;
	std::cout << "Performance read time (clocks) " << (clockEnd-clockBegin) << std::endl;

	//Write file
	std::cout << "Write file " << saveFileName << std::endl;

	clockBegin = clock();
	if (mode == ReadFileWriteFile || mode == ReadGzipWriteFile)
		Asf::writeToFile(saveFileName, asfFile);
	else
		Asf::writeToGzipFile(saveFileName, asfFile);
	clockEnd = clock();

	std::cout << "Performance write time (clocks) " << (clockEnd-clockBegin) << std::endl;
	}

	// Check file
	std::tr1::shared_ptr<Asf::AsfFile> checkedFile;
	std::cout << "File write correctly: "; 
	if (mode == ReadFileWriteFile || mode == ReadGzipWriteFile)
		checkedFile = Asf::createFromFile(saveFileName);
	else
		checkedFile = Asf::createFromGzipFile(saveFileName);

	std::cout << checkedFile->isCorrect() << std::endl;
	std::cout << std::endl;
}

void testAsfFile(const char* inputFileName, const char* inputGzipName)
{
	// test read example files
	const char* inputFileFileName = inputFileName; // was in example.rar
	const char* inputGzipFileName = inputGzipName; // made by 7-zip from previous file

	// write .asf files
	char* outputFileFileName = ".\\Data\\Save\\file_to_file.asf";
	char* outputGzipFileName = ".\\Data\\Save\\gzip_to_file.asf";

	testFile(inputFileFileName, outputFileFileName, ReadFileWriteFile);
	testFile(inputGzipFileName, outputGzipFileName, ReadGzipWriteFile);

	// write .gz files
	char* outputFileGZipName = ".\\Data\\Save\\file_to_gzip.gz";
	char* outputGzipGzipName = ".\\Data\\Save\\gzip_to_gzip.gz";

	testFile(inputFileFileName, outputFileGZipName, ReadFileWriteGzip);
	testFile(inputGzipFileName, outputGzipGzipName, ReadGzipWriteGzip);
}

int main(int argc, char* argv[])
{
	try {
		// input path to test data
		//testAsfFile(".\\Data\\example1.asf",".\\Data\\example1.asf.gz");
		//testAsfFile(".\\Data\\example2.asf",".\\Data\\example2.asf.gz");
		testAsfFile(".\\Data\\example3.asf",".\\Data\\example3.asf.gz");
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error: " << std::endl;
		return 2;
	}

	/*int wait;
	std::cin >> wait;*/
	return 0;
}


