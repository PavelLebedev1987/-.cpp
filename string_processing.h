//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».‎

#pragma once

#include "document.h"

#include<set>
#include<string>
#include <ostream>

template <typename StringContainer>
std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    std::set<std::string> non_empty_strings;
    for (const std::string& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}



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
