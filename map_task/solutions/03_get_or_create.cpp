#include <map>
#include <assert.h>

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


template <class Key, class Value>
class Map {
public:
    struct Proxy {
        template <class Func>
        Proxy(Func f) : val(f()) {}
        Value val;
    };

    template <class Func>
    Value& get_or_create(const Key& key, Func f) {
        return map_.try_emplace(key, f).first->second.val;
    }
    Value* get(const Key& k) {
        if (auto it = map_.find(k); it != map_.end()) {
            return &(it->second.val);
        }
        return nullptr;
    }

    const Value* get(const Key& key) const {
        return const_cast<Map*>(this)->get(key);
    }

private:
    std::map<Key, Proxy> map_;
};

int main() {
  Map<int, int> m;
  
  assert(m.get(1) == nullptr);
  
  assert(m.get_or_create(5, []{return 6;})==6); 
  assert(m.get_or_create(5, []{return 8;})==6);

}
