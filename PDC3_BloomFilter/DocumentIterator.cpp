#include "stdafx.h"
#include "DocumentIterator.h"

DocumentIterator::DocumentIterator(const CassResult * result)
{
	DocumentIterator::result = result;
	if (result != nullptr) {
		rows = cass_iterator_from_result(result);
	}
}

Document * DocumentIterator::getNextDocument()
{
	if (cass_iterator_next(rows)) {
		const CassRow* row = cass_iterator_get_row(rows);
		Document * document = new Document;
		document->documentNumber = getColumnValue(row, DOCUMENT_NUMBER);
		document->documentType = getColumnValue(row, DOCUMENT_TYPE);
		document->countryCode = getColumnValue(row, COUNTRY_CODE);
		return document;
	}
	else {
		return nullptr;
	}
}

DocumentIterator::~DocumentIterator()
{
	cass_result_free(result);
	cass_iterator_free(rows);
}
