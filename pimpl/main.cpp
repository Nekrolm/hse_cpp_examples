#include <iostream>
#include <string_view>

#include "my_string.h"

int main() {
    MyString str("hello");
    std::cout << str.ToStdString() << "\n";
    MyString str2("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaassssssssssssssssssssssaaaaaaaaaaaaaaaaaa");   
    std::cout << str2.ToStdString() << "\n";
}
