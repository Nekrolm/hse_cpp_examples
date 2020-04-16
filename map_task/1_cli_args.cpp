#include <string_view>
#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>

/*
Задача №-1

аргументы командной строки задаются в формате --key=value
используя std::transform + std::inserter, заполните по этим параметрам
std::[unordered_]map<std::string_view, std::string_view>
*/

int main(int argc, char* argv[]) {

  std::map<std::string_view, std::string_view> args;
  //TODO
  
  for (auto [key, value] : args) {
    std::cout << "key=" << key << "; value=" << value << std::endl;
  }

}
