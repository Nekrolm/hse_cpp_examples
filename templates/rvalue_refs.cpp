#include <iostream>
#include <cstring>
#include <type_traits>
#include <utility>

struct Test {
    void print() const & {
        std::cout << "I'm a const lvalue!\n";
    } 

    ~Test() {
        std::cout << "destroyed\n";
    }

    void print() & {
        std::cout << "I'm a lvalue!\n";
    } 

    void print() && {
        std::cout << "I'm a rvalue!\n";
    }

    void print() const && {
        std::cout << "I'm a const rvalue!\n";
    }

    // void print() { std::cout << "I don't know who I am\n";} // compile error
};


Test make_test() {
    return Test{};
}

void printer(Test&& t){
    std::cout << "printer for rvalue: \n";
    t.print();
}

void printer(Test& t){
    std::cout << "printer for lvalue: \n";
    t.print();
}

void printer(const Test& t){
    std::cout << "printer for const lvalue: \n";
    t.print();
}


template <class T>
void template_printer(T&& val) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    val.print();
}

template <class T>
void template_printer_with_forward(T&& val) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::forward<T>(val).print();
}


int main() {

    make_test().print();
    
    {
        std::cout << "----------------\n";
        Test&& rref = make_test();
        rref.print();
        const Test& cref = make_test();
        cref.print();

        Test t;
        t.print();
        const Test& tref = t;
        tref.print();
        std::move(tref).print();
        std::move(t).print();
    }

    {
        std::cout << "----------------\n";
        printer(make_test());
        Test t;
        const Test& cref = t;
        printer(t);
        printer(cref);
    }

    {
        std::cout << "----------------\n";
        template_printer(make_test());
        Test t;
        const Test& cref = t;
        template_printer(t);
        template_printer(cref);
    }

     {
        std::cout << "----------------\n";
        template_printer_with_forward(make_test());
        Test t;
        const Test& cref = t;
        template_printer_with_forward(t);
        template_printer_with_forward(cref);
    }

	return 0;
}
