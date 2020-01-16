#include <iostream>
#include <iomanip>
#include <memory>

class Point {
public:
    Point() = default;
    Point(int x, int y) : x_(x), y_(y) {}

    int Abs() const {
        return x_ * x_ + y_ * y_;
    }


    // point[x,y]
    static auto Read(std::istream& istr) {
        auto point = std::make_unique<Point>();
        std::string line;
        if (istr >> line) {
            if (2 == sscanf(line.c_str(),
                            "point[%d,%d]",
                            &(point->x_),
                            &(point->y_))){
                return point;
            }
            istr.setstate(std::ios_base::badbit);
        }
        point = nullptr;
        return point;
    }


private:
  int x_ = 0;
  int y_ = 0;
};


struct hex_wrapper {
private:

    struct wrapped_istream {
        wrapped_istream(std::istream& strm) : strm(strm) {}
        std::istream& strm;

        friend std::istream& operator >> (const wrapped_istream& w, int& x){
            w.strm >> x;
            w.strm.setf(std::ios_base::dec, std::ios_base::basefield);
            return w.strm;
        }
    };
public:
    auto operator ()(std::istream& strm) const{
        strm.setf(std::ios_base::hex, std::ios_base::basefield);


        return wrapped_istream{strm};
    }
};

hex_wrapper hex;

auto operator >> (std::istream& strm, const hex_wrapper& hexw){
    return hexw(strm);
}

struct one_hex {};


void test_point(){
    Point p;


   if (std::cin >> p){
       std::cout << p.Abs() << "\n";
   } else {
       if (std::cin.bad()){
           std::cout << "bad format\n";
           std::cin.clear(std::ios::badbit);
       }else{
           std::cout << "AAAAAA!\n";
           return EXIT_FAILURE;
       }
   }

   int x;
   if (std::cin >> x){
       std::cout << x << "\n";
   }else{
       std::cout << "bad bit is set\n";
   }


}


int main() {
   test_point();

   // custom iomanip
   int x = 0;
   int y = 0;
   std::cin >> hex >> x >> y;
   std::cout << x << " " << y <<"\n";

    // Voldemort type
    auto wrapped = hex(std::cin);

    {
        using wrapper_name = decltype(hex(std::cin));
        wrapper_name wrapped = hex(std::cin);
    }

    return EXIT_SUCCESS;
}

