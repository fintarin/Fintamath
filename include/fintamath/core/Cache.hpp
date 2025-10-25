#pragma once

#include <functional>
#include <unordered_map>

namespace fintamath::detail {

template <typename Key, typename Value>
class Cache final {
public:
  using Callback = std::function<Value(const Key &)>;

public:
  explicit Cache(const Callback &inKeyToValueCallback) : keyToValueCallback(inKeyToValueCallback) {}

  const Value &operator[](const Key &key) {
    if (auto iter = keyToValueMap.find(key); iter != keyToValueMap.end()) {
      return iter->second;
    }

    const auto iter = keyToValueMap.emplace(key, keyToValueCallback(key)).first;
    return iter->second;
  }

private:
  std::unordered_map<Key, Value> keyToValueMap;

  Callback keyToValueCallback;
};

}
