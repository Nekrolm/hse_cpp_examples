#include <iostream>
#include <cstring>

template <class T>
class MyAllocator {
public:
    T* allocate(size_t n) {
        return reinterpret_cast<T*>(std::aligned_alloc(alignof(T), n * sizeof(T)));
    }
    void deallocate(T* ptr, size_t n) {
        std::free(ptr);
    } 
}; 

template <class T, class Allocator = std::allocator<T> >
class Stack {
public:
    Stack(int limit) : limit_(limit) {
        memory_buffer_ = alloc.allocate(limit_);
    }

    ~Stack() {
        while (!empty()) pop();
        alloc.deallocate(memory_buffer_, limit_);
    }

    bool empty() const {
        return used_ == 0;
    }

    bool full() const {
        return used_ == limit_;
    }

    void pop() {
        top().~T();
        used_--;
    }

    void push(const T& x) {
        emplace_push(x);
    }

    template <class... Args>
    void emplace_push(Args&&... args) {
        new (memory_buffer_ + used_) T(std::forward<Args>(args)...);
        ++used_;
    }

    const T& top() const {
        return memory_buffer_[used_ -1];
    }


    T& top() {
        return memory_buffer_[used_ -1];
    }

private:
    Allocator alloc;

    int used_ = 0;
    int limit_ = 0;
    T* memory_buffer_ = nullptr;
};



int main() {

    Stack<int, MyAllocator<int>> stack(10);

    for (int i = 0; i < 10; ++i)
        stack.push(i);

    while (!stack.empty()){
        std::cout << stack.top() << "\n";
        stack.pop();
    }

	return 0;
}
