#pragma once
#include <cassandra.h>
#include <vector>
#include <time.h>
#include <fstream>
#include "CassandraAdditionalFunctions.h"
#include "DataBaseConfiguration.h"
#include "DocumentIterator.h"
#include "DataBaseHandler.h"
#include "RandomAdditionalOperations.h"
#define DEFAULT_FILE_PATH "documentsTestFile.txt"
#define DEFAULT_POURCENTAGE 0.9999
class TestFileGenerator {
private:
	unsigned int testFileSize;
	string filePath;
	float validDocumentPourcentage;
	DataBaseHandler *dbHandler;
	unsigned int getNonValidDocumentsCount();
	vector<Document*> getNonValidDocuments();
	string generateLine(vector<Document*> * nonValidDocuments, int leftLinesSize);
public:
	TestFileGenerator(unsigned int testFileSize, DataBaseConfiguration dbConf, string filePath = DEFAULT_FILE_PATH, float validDocumentPourcentage = DEFAULT_POURCENTAGE);
	bool generate();
	~TestFileGenerator();
};