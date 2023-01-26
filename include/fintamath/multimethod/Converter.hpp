#pragma once

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/multimethod/MultiMethod.hpp"

namespace fintamath {

class IMathObject;
using MathObjectPtr = std::unique_ptr<IMathObject>;

class Converter {
public:
  template <typename Value, typename Type>
  static void add(const std::function<MathObjectPtr(const Value &value, const Type &type)> &convertFunc) {
    converter.add<Value, Type>(convertFunc);
  }

  static MathObjectPtr convert(const IMathObject &value, const IMathObject &type) {
    return converter(value, type);
  }

  template <typename Type>
  static Type convert(const IMathObject &value) {
    static const Type type;
    return cast<Type>(*convert(value, type));
  }

private:
  static MultiMethod<MathObjectPtr(const IMathObject &, const IMathObject &)> converter;
};

}
