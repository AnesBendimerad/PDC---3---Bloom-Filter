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
unsigned const int documentNumberSize = 25;
unsigned const int documentTypeSize = 3;
unsigned const int countryCodeSize = 3;
string documentToString(Document *document);
Document * stringToDocument(string documentAsString);
// example of documentAsString : 
// "documentNumber documentType countryCode"