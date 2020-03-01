#include <iostream>
#include <cstring>
#include <type_traits>
#include <utility>
#include <tuple>

template <class... Args>
struct always_false : std::false_type {};

template <class... Args>
struct List {
    static_assert(always_false<Args...>::value, "unsupported");
};

// empty list
template <>
struct List<>{};

template <class Head, class... Args>
struct List<Head, List<Args...>> {
    Head head;
    List<Args...> tail;
};

template <class Head, class... Args>
List<Head, List<Args...>> cons (Head x, List<Args...> xs) {
    return { x, xs };
}

template <class Head, class... Args>
Head car(List<Head, List<Args...>> list){
    return list.head;
}

template <class Head, class... Args>
List<Args...> cdr(List<Head, List<Args...>> list){
    return list.tail;
}

template <class List>
void print(List l) {
    std::cout << car(l) << "\n";
    print(cdr(l));
}

template <>
void print(List<>){
    return;
}


const static auto nil = List<>{};

int main() {

    auto L = cons(5, cons(6.7, cons("1231", nil)));

    print(L);

	return 0;
}
