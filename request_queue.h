#pragma once

#include "search_server.h"
#include "document.h"

#include <vector>
#include <string>
#include <deque>




class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server) : search_server_(search_server)
    {    }

    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        std::vector<Document> answer = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddQueryResult(answer);
        return answer;

    }
    std::vector<Document> AddFindRequest(const std::string& raw_query, SearchServer::DocumentStatus status);
    
    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;

private:
    struct QueryResult {
        // определите, что должно быть в структуре
        size_t documents;
        bool IsEmpty() {
            if (documents == 0) {
                return true;
            }
            else return false;
        }

    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_server_;
    int null_queries_ = 0;

    void AddQueryResult(std::vector<Document>& result);
};