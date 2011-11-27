// AsfReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AsfFile.h"
#include "AsfFileUtilities.h"
#include <time.h>

enum TestMode
{
	ReadFileWriteFile,
	ReadFileWriteGzip,
	ReadGzipWriteFile,
	ReadGzipWriteGzip,
};

void testFile(const char * fileName, const char * saveFileName, TestMode mode)
{
	clock_t clockBegin, clockEnd;

	clockBegin = clock();
	std::tr1::shared_ptr<Asf::AsfFile> asfFile;
	if (mode == ReadFileWriteFile || mode == ReadFileWriteGzip)
		asfFile = Asf::createFromFile(fileName);
	else
		asfFile = Asf::createFromGzipFile(fileName);
	clockEnd = clock();

	std::cout << "Check that file " << fileName << " is read correctly : " << asfFile->isCorrect() << std::endl;
	std::cout << "Perfomance read time (clocks) " << (clockEnd-clockBegin) << std::endl;

	clockBegin = clock();
	if (mode == ReadFileWriteFile || mode == ReadGzipWriteFile)
		Asf::writeToFile(saveFileName, asfFile);
	else
		Asf::writeToGzipFile(saveFileName, asfFile);	
	clockEnd = clock();

	std::cout << "Perfomance write time (clocks) " << (clockEnd-clockBegin) << std::endl;
}

void testAsfFile()
{
	char* inputFileName = ".\\Data\\Pure\\example3.asf";
	char* outputFileNameToSave = ".\\Data\\Save\\example3.asf";
	char* outputFileNameGzip = ".\\Data\\GZip\\example3.gz";
	char* outputFileNameGzipFile = ".\\Data\\GZip\\example3.asf";
	
	testFile(inputFileName, outputFileNameToSave, ReadFileWriteFile);
	testFile(outputFileNameToSave, outputFileNameGzip, ReadFileWriteGzip);
	testFile(outputFileNameGzip, outputFileNameGzipFile, ReadGzipWriteFile);
}

int main(int argc, char* argv[])
{
	// Expected 2 parameters inputFileName.txt outputFileName.txt
	if (argc != 3) Asf::printError("wrong number of arguments");

	testAsfFile();

	int wait;
	std::cin >> wait;
	return 0;
}


