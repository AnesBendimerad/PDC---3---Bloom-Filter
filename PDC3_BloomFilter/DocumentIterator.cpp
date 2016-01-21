#include "stdafx.h"
#include "DocumentIterator.h"

DocumentIterator::DocumentIterator(CassSession* session, CassStatement* statement, const CassResult * result)
{
	DocumentIterator::session = session;
	DocumentIterator::statement = statement;
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
	else if (statement == nullptr) {
		return nullptr;
	}
	else if (cass_result_has_more_pages(result)) {
		cass_statement_set_paging_state(statement, result);
		cass_result_free(result);
		CassFuture* future = cass_session_execute(session, statement);
		result = cass_future_get_result(future);
		if (result != nullptr) {
			rows = cass_iterator_from_result(result);
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
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}

//size_t DocumentIterator::getSize()
//{
//	return cass_result_row_count(result);
//}

DocumentIterator::~DocumentIterator()
{
	cass_result_free(result);
	cass_iterator_free(rows);
}
