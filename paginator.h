//Вставьте сюда своё решение из урока «‎Очередь запросов».‎
#pragma once

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
    vector<IteratorRange<Iterator>> pages_;
    Iterator begin_;
    Iterator end_;
    size_t page_size_;
};


template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}