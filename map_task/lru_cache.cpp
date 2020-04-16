#include <map>


/*
Задача №2*:
LRU-кэш. Ассоциативный контейнер с ограниченным числом элементов. 
Если необходимо создать новый элемент, а лимит исчерпан 
-- из контейнера удаляется наиболее долго не используемый элемент.
Также требутеся семантика get_or_create_by

Подсказки/советы:
1. try_emplace скорее всего мало толку
2. std::list может быть полезен (splice)
3. нужен mutable
*/


template <class Key, class Value /*, ????*/>
class LRUCache {
public:
    LRUCache(int limit);
    Key& get_or_create(const Key& key /*func*/);
    Key* get(const Key&);
    const Key* get(const Key&) const;
private:
    //???
};

int main() {
  LRUCache<int, int> m(1);
  
  assert(m.get(1) == nullptr);
  
  assert(m.get_or_create(5, []{return 6;})==6); 
  assert(m.get_or_create(4, []{return 8;})==8); // вытеснение
  assert(m.get_or_create(5, []{return 8;})==8);

}
