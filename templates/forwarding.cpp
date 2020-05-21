#include <vector>
#include <memory>
#include <utility>
#include <iostream>

template <class T>
decltype(auto) PerfectForward(T&& x){
    return std::forward<T>(x);
}

static const auto PerfectForwardLambda = [](auto&& x) -> decltype(auto) {
    return std::forward<decltype(x)>(x);
};


template <class Function, class Arg>
decltype(auto) PerfectForwardFuncCall(Function&& f, Arg&& arg) {
    return std::forward<Function>(f)(std::forward<Arg>(arg));
}

int& increment(int& x){
    x += 1;
    return x;
}

//------------------------------
struct NonStackStruct {
private:
    struct CreateTag {};
public:    
    int a;
    int b;
    float c;


    template <class... Args>
    static std::unique_ptr<NonStackStruct> Make(Args&&... args) {
        return std::make_unique<NonStackStruct>(CreateTag{}, std::forward<Args>(args)...);
    }

    template <class... Args>
    NonStackStruct(CreateTag, Args&&... args) : NonStackStruct(std::forward<Args>(args)...) {} 
private:
    NonStackStruct(int a_, int b_, float c_) : a(a_), b(b_), c(c_) {}
    NonStackStruct(const std::string& s) : a(s.length()), b(s.capacity()), c(5) {}
};

//-----------------------------

int main(){
    auto item = NonStackStruct::Make(1,2,3);
}





