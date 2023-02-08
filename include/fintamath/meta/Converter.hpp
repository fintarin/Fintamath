#pragma once

#include <memory>

#include "fintamath/meta/MultiMethod.hpp"

namespace fintamath {

class IMathObject;
using MathObjectPtr = std::unique_ptr<IMathObject>;

class Converter {
public:
  template <typename Value, typename Type>
  static void add(const std::function<MathObjectPtr(const Value &value, const Type &type)> &convertFunc) {
    converter.add<Value, Type>(convertFunc);
  }

  static MathObjectPtr convert(const IMathObject &from, const IMathObject &to) {
    return converter(from, to);
  }

private:
  static MultiMethod<MathObjectPtr(const IMathObject &, const IMathObject &)> converter;
};

}
