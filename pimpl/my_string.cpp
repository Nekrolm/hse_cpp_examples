 

#include "my_string.h"

#include <string>
#include <string_view>
#include <variant>
#include <iostream>


template <class... F>
struct OverloadSet : F... {
    using F::operator()...;
};

template <class... F> 
auto MakeOverloads(F... f) {
    return OverloadSet<F...>{ f... };
}

template <class... F>
OverloadSet(F...) -> OverloadSet<F...>;

class MyString::MyStringImpl { 
public:
    std::string_view ToStdString() const {
        return std::visit(MakeOverloads([](const ShortString& s){
            std::clog << "Short string\n";
            return std::string_view(s.str); 
        },
        [](const std::string& str){
            std::clog << "Normal string\n";
            return std::string_view(str);
        }), str_storage);
    } 

    MyStringImpl(std::string_view v) 
    : str_storage([v]()->Storage{
        if (v.length() < sizeof(std::string)){
            ShortString str;
            std::copy(std::begin(v), std::end(v), str.str);
            return str;
        }else{
            return std::string(v);
        }
    }()) {}

private:
    struct ShortString {
        char str[sizeof(std::string)] = {};
    };

  using Storage = std::variant<ShortString, std::string>;   
  
  Storage str_storage;
};

MyString::MyString(std::string_view sv) {
    impl_ = std::make_unique<MyStringImpl>(sv);
}

std::string_view MyString::ToStdString() const {
    return impl_->ToStdString();
}

MyString::~MyString() = default;