#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <any>
#include <iterator>



template <class IterBegin, class IterEnd>
struct ForwardIterator {
    IterBegin current;
    IterEnd end;

    bool HasValue () const {
        return current != end;
    }

    void Next() {
        ++current;
    }

    auto Value() const {
        return *current;
    }

};



template <class FwdIter, class Functor>
struct TransformIterator {
    FwdIter iter;
    Functor f;

    bool HasValue() const {
        return iter.HasValue();
    }

    void Next() {
        iter.Next();
    }

    auto Value() const {
        return f(iter.Value());
    }
};

template <class FwdIterT>
struct Enumerable {
    FwdIterT iter;

    template <class Functor> 
    auto Select(Functor f) {
        using NewIter = TransformIterator<FwdIterT, Functor>;
        using NewEnumerable = Enumerable<NewIter>;
        return NewEnumerable {  NewIter { iter, f } }; 
    }

    template <class OutputIteratorT>
    void CopyTo(OutputIteratorT out) {
        while (iter.HasValue()){
            *out = iter.Value();
            ++out;
            iter.Next();
        }
    }

    auto ToVector() {
        using ValueT = std::decay_t<decltype(iter.Value())>;
        std::vector<ValueT> v;
        CopyTo(std::back_inserter(v));
        return v;
    }
};

template <class BeginIter, class EndIter>
auto From(BeginIter begin, EndIter end) {
    using FwdIter = ForwardIterator<BeginIter, EndIter>;
    using NewEnumerable = Enumerable<FwdIter>;
    return NewEnumerable { FwdIter {begin, end} };
}


int main() {
    int x[] { 1,2,3,4,5};

    auto v = From(std::begin(x), std::end(x))
    .Select([](auto val){ return val * val + 0.5;  })
    .Select([](auto val){ return  "/" + std::to_string(val) + "/"; })
    .ToVector();

    for (auto val : v) {
        std::cout << val << " ";
    }
    
}
