#pragma once

#include <memory>

#include "fintamath/core/CoreDefines.hpp"
#include "fintamath/meta/MultiMethod.hpp"

namespace fintamath {

class IMathObject;

class Converter {
public:
  template <typename Type, typename Value>
  static void add(const function<unique_ptr<IMathObject>(const Type &type, const Value &value)> &convertFunc) {
    converter.add<Type, Value>(convertFunc);
  }

  static unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from) {
    return converter(to, from);
  }

private:
  static MultiMethod<unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> converter;
};

}
