#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <any>
#include <iterator>
#include <sstream>
#include <chrono>

namespace detail {

template <class T, class = void>
struct is_printable : std::false_type {};

template <class T>
struct is_printable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

template <class T, class = void>
struct has_to_string : std::false_type {};

template <class T>
struct has_to_string<T, 
                    std::enable_if<
                            std::is_same_v<decltype(std::declval<T>().to_string()), 
                                            std::string>
                                >
                    > : std::true_type {};

} 

template <class T> 
struct is_printable : detail::is_printable<T> {};

template <class T>
constexpr auto is_printable_v = is_printable<T>::value;

template <class T> 
struct has_to_string : detail::has_to_string<T> {};

template <class T>
constexpr auto has_to_string_v = has_to_string<T>::value;


template <class T>
void print(const T& x){
    if constexpr (has_to_string_v<T>) {
        std::cout << x.to_string() << "\n";
    } else if constexpr (is_printable_v<T>) {
        std::cout << x << "\n";
    } else {
        static_assert(has_to_string_v<T> || is_printable_v<T>, "can't print");
    }
}


// template <class T>
// void print(const T& x) {
//     std::cout << x << "\n";
// }


// template <class T, class = decltype(std::cout << std::declval<T>())>
// void print(const T& x) {
//     std::cout << x;
// }


template <class T>
struct MyVector : private std::vector<T> {
    using base = std::vector<T>;
    
    using base::base; // forward ctors
    using base::begin;
    using base::end;
    using base::size;
    using base::operator[];
 

    template <class ValueT = T, class = std::enable_if_t<is_printable_v<ValueT>>>
    void print() const {
        std::cout << "[";
        for (const auto& x : *this) {
            std::cout << " " << x;
        }
        std::cout << " ]";
    }
};




int main() {
    print(1);
    std::pair<int, int> x = {1,2};
    // print(x);

    MyVector<int> v1 = {1,2,3,4,5};
    v1.print();
    MyVector<std::pair<int,int>> v2 = { {1, 2}, {2,3}};
    // v2.print();
}





