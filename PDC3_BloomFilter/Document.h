#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#define DOCUMENT_NUMBER "documentNumber"
#define DOCUMENT_TYPE "documentType"
#define COUNTRY_CODE "countryCode"
using namespace std;

typedef struct Document {
	string documentNumber;
	string documentType;
	string countryCode;
} Document;
string documentToString(Document *document);
Document * stringToDocument(string documentAsString);
// example of documentAsString : 
// "documentNumber documentType countryCode"