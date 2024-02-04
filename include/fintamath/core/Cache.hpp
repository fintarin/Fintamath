#pragma once

#include <functional>
#include <unordered_map>

namespace fintamath {

template <typename Key, typename Value>
class Cache final {
public:
  using Function = std::function<Value(const Key &)>;

public:
  explicit Cache(const Function &keyToValueFunction) : func(keyToValueFunction) {}

  const Value &operator[](const Key &key) {
    if (!map.contains(key)) {
      map[key] = func(key);
    }

    return map.at(key);
  }

private:
  std::unordered_map<Key, Value> map;

  Function func;
};

}
