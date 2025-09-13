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
public:
  static SharedPtr<IMathObject> convert(MathObjectClass toClass, const SharedRef<IMathObject> &from);

  template <typename To, typename From>
  static void add();

private:
  using ClassPair = std::pair<MathObjectClass, MathObjectClass>;

  using ConvertCallback = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &)>;

  using ClassPairToCallbackMap = std::unordered_map<ClassPair, ConvertCallback, Hash<ClassPair>>;

private:
  static ClassPairToCallbackMap &getClassPairToCallbackMap();
};

template <typename To, typename From>
inline void Converter::add() {
  getClassPairToCallbackMap().emplace(
    ClassPair{To::getClassStatic(), From::getClassStatic()},
    [](const SharedRef<IMathObject> &from) {
      return makeShared<To>(castChecked<From>(*from));
    }
  );
}

}

template <std::derived_from<IMathObject> From>
SharedPtr<IMathObject> convert(MathObjectClass toClass, const SharedRef<From> &from) {
  return detail::Converter::convert(toClass, from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
SharedPtr<To> convert(const SharedRef<To> &to, const SharedRef<From> &from) {
  return cast<To>(detail::Converter::convert(to->getClass(), from));
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
SharedPtr<To> convert(const SharedRef<From> &from) {
  return cast<To>(convert(To::getClassStatic(), from));
}

}
