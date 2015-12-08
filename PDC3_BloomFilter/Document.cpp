#include "stdafx.h"
#include "Document.h"
string documentToString(Document *document) {
	return document->documentNumber + " " + document->documentType + " " + document->countryCode;

}
Document * stringToDocument(string documentAsString) {
	istringstream iss(documentAsString);
	vector<string> tokens{ istream_iterator<string>{iss},istream_iterator<string>{} };
	if (tokens.size() != 3) {
		return nullptr;
	}
	Document * doc = new Document;
	doc->documentNumber = tokens[0];
	doc->documentType = tokens[1];
	doc->countryCode = tokens[2];
	return doc;
}