#include "fintamath/core/Converter.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath::detail {

SharedPtr<IMathObject> Converter::convert(MathObjectClass toClass, const SharedRef<IMathObject> &from) {
  const MathObjectClass fromClass = from->getClass();
  if (toClass == from->getClass()) {
    return from;
  }

  const auto &map = getClassPairToCallbackMap();
  auto iter = map.find(ClassPair{toClass, fromClass});
  return iter != map.end() ? iter->second(from) : SharedPtr<IMathObject>{};
}

Converter::ClassPairToCallbackMap &Converter::getClassPairToCallbackMap() {
  static ClassPairToCallbackMap classPairToCallbackMap;
  return classPairToCallbackMap;
}

}