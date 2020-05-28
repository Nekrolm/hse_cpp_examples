#pragma once

#include <memory>
#include <string>
#include <string_view>



class MyString {
public:
    MyString(std::string_view);

    MyString(MyString&&) = default;
    ~MyString();
    MyString& operator = (MyString&&) = default;
    
    std::string_view ToStdString() const;
private:
    class MyStringImpl;
    std::unique_ptr<MyStringImpl> impl_;
};
