#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <ostream>

#include "search_server.h"



template <typename Iterator>
class IteratorRange {

public:

    explicit IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) { }

    Iterator begin() {
        return begin_;
    }

    Iterator end() {
        return end_;
    }

    size_t GetSize() {
        return distance(begin_, end_);
    }
private:

    Iterator begin_;
    Iterator end_;

};

std::ostream& operator<<(std::ostream& out, const Document& doc);

template <typename Iterator>
std::ostream& operator<<(std::ostream& out, IteratorRange<Iterator> iter) {
    for (auto it = iter.begin(); it != iter.end(); ++it) {
        out << *it;
    }
    return out;
}

template <typename Iterator>
class Paginator {
    // тело класса
public:
    explicit Paginator(Iterator begin, Iterator end, size_t page_size) :
        begin_(begin), end_(end), page_size_(page_size) {
        GetPages();
    }


    void GetPages() {
        Iterator run = begin_;
        size_t distance = 0;

        for (Iterator i = begin_; i != end_; i++) {

            distance++;

            if (distance == page_size_) {
                IteratorRange<Iterator> page(run, run + page_size_);
                pages_.push_back(page);
                advance(run, page_size_);
                distance = 0;
            }
        }
        if (run != end_) {
            pages_.push_back(IteratorRange{ run, end_ });
        }
    }

    const auto begin() const {
        return pages_.begin();
    }
    const auto end() const {
        return pages_.end();
    }


private:
    std::vector<IteratorRange<Iterator>> pages_;
    Iterator begin_;
    Iterator end_;
    size_t page_size_;
};


template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}