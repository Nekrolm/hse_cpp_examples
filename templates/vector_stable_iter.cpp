#include <iostream>
#include <cstring>
#include <type_traits>
#include <utility>
#include <memory>

// represent only memory
template <typename T, class Alloc = std::allocator<T>>
struct vector_base {
    using AllocTrait = std::allocator_traits<Alloc>;

    vector_base() noexcept = default;

    vector_base(size_t capacity){
        if (capacity == 0) return;
        // adjust capacity to power of 2
        space_ = storage_ = AllocTrait::allocate(allocator_, capacity);
        storage_end_ = storage_ + capacity;
    }

    ~vector_base() {
        if (storage_) AllocTrait::deallocate(allocator_, storage_, storage_end_ - storage_);
    }

    void swap(vector_base& other) noexcept {
        std::swap(storage_, other.storage_);
        std::swap(space_, other.space_);
        std::swap(storage_end_, other.storage_end_);
        std::swap(allocator_, other.allocator_);
    }

    vector_base(const vector_base&) = delete;
    vector_base(vector_base&& other) noexcept {
        swap(other);
    }
    vector_base& operator = (const vector_base&) = delete;
    vector_base& operator = (vector_base&& other) noexcept {
        swap(other);
        return *this;
    }

    size_t capacity() const noexcept {
        return storage_end_ - storage_;
    }

    size_t size() const noexcept {
        return space_ - storage_;
    }

    T* storage_ = nullptr;
    T* space_ = nullptr;
    T* storage_end_ = nullptr;
    Alloc allocator_;
};



template <typename T, class Alloc = std::allocator<T>>
class vector : private vector_base<T, Alloc> {
private:
    using base = vector_base<T, Alloc>;
    using AllocTrait = typename base::AllocTrait;
public:
    template <class VectorT>
    struct Iterator;

    vector() = default;
    vector(size_t n) : base(n) {
        std::uninitialized_value_construct_n(begin(), n);
        space_ += n;
    }


    ~vector() { clear(); }

    vector(size_t n, const T& default_value) : base(n) {
        std::uninitialized_fill_n(space_, n, default_value);
        space_ += n;
    }

    vector(vector&& other) noexcept { base::swap(other); }
    vector(const vector& other) : base(other.size()) {
        std::uninitialized_copy_n(other.begin(), other.size(), begin());
        space_ += other.size();
    }

    vector& operator = (vector&& other) noexcept {
        base::swap(other);
        return *this;
    }

    vector& operator = (const vector& other) {
        vector tmp(other);
        return *this = std::move(tmp);
    }

    void pop_back() noexcept {
        AllocTrait::destroy(allocator_, space_ - 1);
        space_--;      
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity())
            return;
        base new_base(new_capacity);
        std::uninitialized_move_n(begin(), size(), new_base.space_);
        new_base.space_ += size();
        clear();
        base::swap(new_base);
    }

    void resize(size_t new_size) {
        if (new_size <= size()){
            while(new_size < size()){
                pop_back();
            }
            return;
        }
        size_t construct_cnt = new_size - size();
        if (new_size <= capacity()){
            std::uninitialized_value_construct_n(begin(), construct_cnt);
            space_ += construct_cnt;
        } else{
            base new_base(new_size);
            std::uninitialized_value_construct_n(new_base.space_ + size(), construct_cnt);
            std::uninitialized_move_n(begin(), size(), new_base.space_);
            new_base.space_ += new_size;
            base::swap(new_base);
        }
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
        if (size() < capacity()) {
            AllocTrait::construct(allocator_, space_, std::forward<Args>(args)...);
	        space_++;
            return;
        }
        base new_base(std::max(static_cast<size_t>(1), capacity() * 2));
        AllocTrait::construct(new_base.allocator_, new_base.space_ + size(), std::forward<Args>(args)...);
        std::uninitialized_move_n(storage_, size(), new_base.space_);
        new_base.space_ += size() + 1;
        base::swap(new_base);
    }

    void push_back(const T& v) {
        emplace_back(v);
    }

    const T& operator [] (size_t i) const {
        return begin()[i];
    }

    T& operator [] (size_t i) {
        return storage_[i];
    }

    using base::capacity;
    using base::size;


    bool empty() const noexcept {
        return size() == 0;
    }

    void clear() noexcept {
        while (!empty())
            pop_back();
    }


    template <class VectorT>
    struct Iterator {
        using value_type = T;
        using pointer = decltype(&(std::declval<VectorT>()[0]));
        using reference = decltype(std::declval<VectorT>()[0]);

        reference operator * () const {
            return vector_[n_];
        }

        Iterator& operator ++ () {
            n_++;
            return *this;
        }

        friend bool operator == (const Iterator& lhs, const Iterator& rhs){
            return (&lhs.vector_ == &rhs.vector_) && lhs.n_ == rhs.n_;
        }

        friend bool operator != (const Iterator& lhs, const Iterator& rhs){
            return !(lhs == rhs);
        }
        
        VectorT& vector_;   
        int n_;
    };

    auto begin() {
        return Iterator<decltype(*this)>{*this, 0};
    }

    auto begin() const {
        return Iterator<decltype(*this)>{*this, 0};
    }


    auto end() {
        return Iterator<decltype(*this)>{*this, static_cast<int>(size())};
    }

    auto end() const {
        return Iterator<decltype(*this)>{*this, static_cast<int>(size())};
   
    }


private:
    using base::allocator_;
    using base::space_;
    using base::storage_;
};

//------------------------------------
int main() {

    vector<int> v;
    v.push_back(1);
    v.push_back(2);

    std::cout << v.size() << "\n";
    std::cout << v.capacity() << "\n";
    
    for (auto x : v)
        std::cout << x << " ";

    std::cout << "\n";

    vector<std::string> vs(5, "ololo");
    
    std::cout << vs.size() << "\n";
    std::cout << vs.capacity() << "\n";

    for (auto& x : vs) {
        x = "23213";
    }

    for (auto& x : vs) {
        std::cout << x << " ";
    }
    

        
    // const auto& cvs = vs;

    // for (auto& x : cvs) {
    //     x = "23213";
    // }


	return 0;
}
