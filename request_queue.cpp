#include "request_queue.h"

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, SearchServer::DocumentStatus status) {
    // напишите реализацию
    std::vector<Document> answer = search_server_.FindTopDocuments(raw_query, status);
    AddQueryResult(answer);
    return answer;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    // напишите реализацию
    std::vector<Document> answer = search_server_.FindTopDocuments(raw_query);
    AddQueryResult(answer);
    return answer;
}

int RequestQueue::GetNoResultRequests() const {
    return null_queries_;
}

void RequestQueue::AddQueryResult(std::vector<Document>& result) {
    if (requests_.size() == min_in_day_) {
        if (requests_.front().IsEmpty()) {
            --null_queries_;
        }
        requests_.pop_front();
    }

    QueryResult query_result = { result.size() };
    requests_.push_back(query_result);
    if (query_result.IsEmpty()) {
        ++null_queries_;
    }
}
