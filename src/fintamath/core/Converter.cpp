#include "fintamath/core/Converter.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath::detail {

Shared<IMathObject> Converter::convert(MathObjectClass toClass, const Shared<IMathObject> &from) {
  if (!from) {
    throw InvalidInputException("Argument 'from' is null");
  }

  const MathObjectClass fromClass = from->getClass();
  if (toClass == from->getClass()) {
    return from;
  }

  const auto& map = getClassPairToCallbackMap();
  auto iter = map.find(ClassPair{toClass, fromClass});
  return iter != map.end() ? iter->second(from) : nullptr;
}

Converter::ClassPairToCallbackMap &Converter::getClassPairToCallbackMap() {
  static ClassPairToCallbackMap classPairToCallbackMap;
  return classPairToCallbackMap;
}

}