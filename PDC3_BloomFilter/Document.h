#pragma once
#include <string>
#define DOCUMENT_NUMBER "documentNumber"
#define DOCUMENT_TYPE "documentType"
#define COUNTRY_CODE "countryCode"
using namespace std;

typedef struct Document {
	string documentNumber;
	string documentType;
	string countryCode;
} Document;