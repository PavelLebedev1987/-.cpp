#include "string_processing.h"  


std::ostream& operator<<(std::ostream& out, const Document& doc) {
    out << "{ document_id = " << doc.id << ", relevance = " << doc.relevance << ", rating = " << doc.rating << " }";
    return out;
}