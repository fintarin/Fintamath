#pragma once

#include <memory>

namespace fintamath {

class IMathObject;

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Shared = std::shared_ptr<const T>;

template <std::derived_from<IMathObject> T, typename... Args>
Unique<T> makeUnique(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <std::derived_from<IMathObject> T, typename... Args>
Shared<T> makeShared(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

}
