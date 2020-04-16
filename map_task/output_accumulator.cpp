#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

/*
Задача №0
std::transform + accumulate_output_iterator:

Реализовать итератор, позволяющий выполнить суммирование чисел, 
заданных контейнером строк, "однострочником" вида:

int result = 0;
std::transform(std::begin(v), 
               std::end(v), 
               accumulate_output_iterator(result), 
               parse_int);


Подсказки/советы:
1. accumulate_output_iterator -- шаблонная функция
2. https://en.cppreference.com/w/cpp/named_req/OutputIterator
3. определите структуру для итератора в скоупе функции
*/

//TODO: accumulate_iterator

int main(int argc, char* argv[]) {

  std::vector<std::string> input = {"1", "2", "3"};
  
  int sum = 0;
  std::transform(std::begin(input), std::end(input), accumulate_iterator(sum), [](auto s){
    return std::stoi(s);
  });
  
  assert(sum == 6);

}
