#include "stdafx.h"
#include "TestFileGenerator.h"

TestFileGenerator::TestFileGenerator(DataBaseHandler *dbHandler, unsigned int testFileSize, float validDocumentPourcentage, string filePath)
{
	TestFileGenerator::testFileSize = testFileSize;
	TestFileGenerator::filePath = filePath;
	TestFileGenerator::validDocumentPourcentage = validDocumentPourcentage;
	TestFileGenerator::dbHandler = dbHandler;
}

unsigned int TestFileGenerator::getNonValidDocumentsCount()
{
	return unsigned int(ceil(testFileSize*(1- validDocumentPourcentage)));
}

vector<Document*> TestFileGenerator::getNonValidDocuments()
{
	unsigned int dbSize = dbHandler->getDataBaseSize();
	DocumentIterator * docIterator = dbHandler->getDocumentIterator();
	vector<unsigned int> randomIntegers = getOrderedListOfRandomIntegers(getNonValidDocumentsCount(), dbSize);
	vector<Document*> nonValidDocuments;
	if (randomIntegers.size() == 0) {
		return nonValidDocuments;
	}
	int i = 0;
	int j = 0;
	bool continu = true;
	Document * currentDocument= docIterator->getNextDocument();
	while (continu) {
		if (randomIntegers[j] == i) {
			j++;
			nonValidDocuments.push_back(currentDocument);
		}
		else {
			currentDocument = docIterator->getNextDocument();
			i++;
		}
		if (j == randomIntegers.size()) {
			continu = false;
		}
	}
	return nonValidDocuments;
}
string TestFileGenerator::generateLine(vector<Document*> * nonValidDocuments, int leftLinesSize)
{
	unsigned int index=rand() % leftLinesSize;
	string result = "";
	if (index < nonValidDocuments->size()) {
		result = (*nonValidDocuments)[index]->documentNumber + " 1";
		nonValidDocuments->erase(nonValidDocuments->begin() + index);
		return result;
	}
	else {
		string randomDocumentNumber = getRandomString(documentNumberSize);
		Document *doc = dbHandler->getDocumentByNumber(randomDocumentNumber);
		if (doc == nullptr) {
			result = randomDocumentNumber + " 0";
			return result;
		}
		else {
			result = randomDocumentNumber + " 1";
			delete doc;
			return result;
		}
	}
}
bool TestFileGenerator::generate()
{
	srand(time(NULL));
	vector<Document*> nonValidDocuments=getNonValidDocuments();
	ofstream outputStream(filePath, ios::out);
	if (outputStream.fail()) {
		throw runtime_error("Failed when openning file");
	}
	for (unsigned int i = 0; i < testFileSize; i++) {
		string str = generateLine(&nonValidDocuments, testFileSize - i);
		if (i < testFileSize - 1) {
			outputStream << str << endl;
		}
		else {
			outputStream << str;
		}
	}
	outputStream.close();
	return true;
}

TestFileGenerator::~TestFileGenerator()
{
	delete dbHandler;
}
