#include <iterator>
#include <type_traits>
#include <iostream>
#include <list>
#include <vector>

// Задача: "умный бинарный поиск"
// есть std::binary_search -- работает с любым типом итераторов
// для random_access_iterator временная сложность O(log(distance(begin, end)))
// для остальных типов итераторов деградирует до O(distance(begin, end))
// при этом работает медленнее обычного линейного поиска (из-за бесполезных попыток деления пополам)
// нужно:
// 1. Написать свой binary_search, работающий с любым типом итераторов
//    a) Для random_access -- бинарный поиск
//    b) Для остальных переключается на линейный
// 2. Написать свой random_access_iterator (например, range чисел)
// 3. Протестировать binary_search на новом итераторе, std::vector, std::list  


template <class T>
struct always_false : std::false_type {};


namespace detail {

template <class IteratorT, class ElementT>
bool bin_search_impl(std::random_access_iterator_tag, IteratorT begin_it, IteratorT end_it, ElementT element) {
    // ...
    const auto original_end = end_it;
    while (begin_it != end_it){
        auto n = end_it - begin_it;
        auto mid_it = begin_it + n / 2;
        if (*mid_it < element){
            begin_it = mid_it + 1;
        } else{
            end_it = mid_it;
        }
    }

    return (begin_it != original_end) && *begin_it == element;
}


template <class TagT, class IteratorT, class ElementT>
bool bin_search_impl(TagT, IteratorT begin_it, IteratorT end_it, ElementT el) {
    // ...
    std::cout << "othres\n";
    while (begin_it != end_it && *begin_it < el) ++begin_it;

    return (begin_it != end_it) && *begin_it == el;
}




template <class IteratorT, class ElementT>
bool bin_search_impl(std::input_iterator_tag, IteratorT, IteratorT, ElementT) {
    static_assert(always_false<ElementT>::value, "unsupported for input_iterator");
    return false;
}

}


template <class IteratorT, class ElementT>
bool binary_search( IteratorT begin_it, IteratorT end_it, ElementT el) {
    using iterator_tag = typename std::iterator_traits<IteratorT>::iterator_category;
    return detail::bin_search_impl(iterator_tag{}, begin_it, end_it, el);
}


///--------------------

struct IntegerRange {

    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = int;
        using value_type = int;
        using reference = int;
        using pointer = void;

        reference operator* () const {
            return value_;
        }
        Iterator& operator ++ () {
            value_++;
            return *this;
        }

        Iterator& operator -- () {
            value_--;
            return *this;
        }

        Iterator& operator += (difference_type n) {
            value_ += n;
            return *this;
        }

        Iterator& operator -= (difference_type n) {
            value_ -= n;
            return *this;
        }

        friend Iterator operator + (Iterator it, difference_type n) {
            it += n;
            return it;    
        }    

        friend bool operator == (const Iterator& lhs, const Iterator& rhs) {
            return lhs.value_ == rhs.value_;
        }

        friend difference_type operator - (const Iterator& lhs, const Iterator& rhs) {
            return lhs.value_ - rhs.value_;
        }

        friend bool operator != (const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }
        
        value_type value_;
    };

    auto begin() const {
        return Iterator{begin_};
    }

    auto end() const {
        return Iterator{end_};
    }
    

    int begin_;
    int end_;
};


int main() {
    std::vector<int> v = {-1,0,0,0,1};
    std::list<int> l = {-5, 0, 1, 2, 4, 5, 8};

    auto r = IntegerRange{1, 5};

    std::cout << binary_search(std::begin(v), std::end(v), 1) << "\n";
    std::cout << binary_search(std::begin(l), std::end(l), 3) << "\n";
    std::cout << binary_search(std::begin(r), std::end(r), 3) << "\n";
    

    // binary_search(std::istream_iterator<int>(std::cin), std::istream_iterator<int>{}, 5);

}
