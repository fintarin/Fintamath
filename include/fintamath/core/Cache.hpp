#pragma once

#include <functional>
#include <unordered_map>

namespace fintamath::detail {

template <typename Key, typename Value>
class Cache final {
public:
  using Function = std::function<Value(const Key &)>;

public:
  explicit Cache(const Function &inKeyToValueFunction) : keyToValueFunction(inKeyToValueFunction) {}

  const Value &operator[](const Key &key) {
    if (!keyToValueMap.contains(key)) {
      keyToValueMap[key] = keyToValueFunction(key);
    }

    return keyToValueMap.at(key);
  }

private:
  std::unordered_map<Key, Value> keyToValueMap;

  Function keyToValueFunction;
};

}
