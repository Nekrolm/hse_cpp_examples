#include <map>


/*
Задача №1:
Ассоциативный контейнер с семантикой get_or_create_by:
Если в контейнере есть значение, соответсвующее ключу, возвращается оно. 
Иначе -- выполняется отложенный вызов функции (функционального объекта), создающей новое значение 

Подсказки:
1. try_emplace стандартных контейнеров
2. вспомогательная структура с особым конструктором
3. Используйте шаблоны для вызываемого объекта
*/


template <class Key, class Value /*, ????*/>
class Map {
public:
    Key& get_or_create(const Key& key /*func*/);
    Key* get(const Key&);
    const Key* get(const Key&) const;
private:
    //???
};

int main() {
  Map<int, int> m;
  
  assert(m.get(1) == nullptr);
  
  assert(m.get_or_create(5, []{return 6;})==6); 
  assert(m.get_or_create(5, []{return 8;})==6);

}
