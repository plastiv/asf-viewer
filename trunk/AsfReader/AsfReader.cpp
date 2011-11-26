// AsfReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AsfFile.h"
#include "AsfFileUtilities.h"

void testAsfFile()
{
	char* inputFileName = ".\\Data\\Pure\\example3.asf";
	char* outputFileNameToSave = ".\\Data\\Save\\example3.asf";
	char* outputFileNameGzip = ".\\Data\\GZip\\example3.gz";

	std::tr1::shared_ptr<Asf::AsfFile> asfFile = Asf::createFromFile(inputFileName);
	std::cout << "Check that file " << inputFileName << " is read correctly : " << asfFile->isCorrect() << std::endl;
	Asf::writeToFile(outputFileNameToSave, asfFile);

	std::tr1::shared_ptr<Asf::AsfFile> asfNewFile = Asf::createFromFile(outputFileNameToSave);
	std::cout << "Check that file " << outputFileNameToSave << " is read correctly : " << asfNewFile->isCorrect() << std::endl;
	Asf::writeToGzipFile(outputFileNameGzip, asfNewFile);

	std::tr1::shared_ptr<Asf::AsfFile> asfZipFile = Asf::createFromGzipFile(outputFileNameGzip);
	std::cout << "Check that file " << outputFileNameGzip << " is read correctly : " << asfZipFile->isCorrect() << std::endl;
}

int main(int argc, char* argv[])
{
	// Expected 2 parameters inputFileName.txt outputFileName.txt
	if (argc != 3) Asf::printError("wrong number of arguments");

	testAsfFile();
	//std::tr1::shared_ptr<Asf::AsfFile> asfZipFile = Asf::createFromGzipFile(".\\Data\\Pure\\example3.asf.gz");
	//std::cout << "Check that file " << ".\\Data\\Pure\\example3.asf.gz" << " is read correctly : " << asfZipFile->isCorrect() << std::endl;

	return 0;
}


