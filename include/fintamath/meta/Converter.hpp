#pragma once

#include <memory>

#include "fintamath/core/CoreDefines.hpp"
#include "fintamath/meta/MultiMethod.hpp"

namespace fintamath {

class IMathObject;

class Converter {
public:
  template <typename Value, typename Type>
  static void add(const function<unique_ptr<IMathObject>(const Value &value, const Type &type)> &convertFunc) {
    converter.add<Value, Type>(convertFunc);
  }

  static unique_ptr<IMathObject> convert(const IMathObject &from, const IMathObject &to) {
    return converter(from, to);
  }

private:
  static MultiMethod<unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> converter;
};

}
