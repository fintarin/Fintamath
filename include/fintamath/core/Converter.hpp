#pragma once

#include <concepts>
#include <functional>
#include <unordered_map>

#include "fintamath/core/Hash.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

class IMathObject;

namespace detail {

class Converter final {
  using ClassPair = std::pair<MathObjectClass, MathObjectClass>;

  using ConvertCallback = std::function<Shared<IMathObject>(const Shared<IMathObject> &)>;

  using ClassPairToCallbackMap = std::unordered_map<ClassPair, ConvertCallback, Hash<ClassPair>>;

public:
  static Shared<IMathObject> convert(MathObjectClass toClass, const Shared<IMathObject> &from);

  template <typename To, typename From>
  static void add();

private:
  static ClassPairToCallbackMap &getClassPairToCallbackMap();
};

template <typename To, typename From>
inline void Converter::add() {
  getClassPairToCallbackMap().emplace(
    ClassPair{To::getClassStatic(), From::getClassStatic()},
    [](const Shared<IMathObject> &from) {
      return makeShared<To>(cast<From>(*from));
    }
  );
}

}

template <std::derived_from<IMathObject> From>
Shared<IMathObject> convert(MathObjectClass toClass, const Shared<From> &from) {
  return detail::Converter::convert(toClass, from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
Shared<To> convert(const Shared<To> &to, const Shared<From> &from) {
  assert(from);
  return cast<To>(detail::Converter::convert(to->getClass(), from));
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
Shared<To> convert(const Shared<From> &from) {
  return cast<To>(convert(To::getClassStatic(), from));
}

}
