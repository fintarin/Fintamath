#pragma once

#include <memory>

#include "fintamath/core/MultiMethod.hpp"

#define REQUIRE_MATH_OBJECTS(To, From)                                                                                 \
  template <typename To, typename From,                                                                                \
            typename = std::enable_if_t<std::is_base_of_v<IMathObject, To> && std::is_base_of_v<IMathObject, From>>>

namespace fintamath {

class IMathObject;

class Converter {
  REQUIRE_MATH_OBJECTS(Type, Value)
  using ConverterFunction = std::function<std::unique_ptr<IMathObject>(const Type &type, const Value &value)>;

public:
  REQUIRE_MATH_OBJECTS(Type, Value) static void add(const ConverterFunction<Type, Value> &convertFunc) {
    getConverter().add<Type, Value>(convertFunc);
  }

  static std::unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from) {
    return getConverter()(to, from);
  }

private:
  static MultiMethod<std::unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> &getConverter();
};

REQUIRE_MATH_OBJECTS(To, From) std::unique_ptr<IMathObject> convert(const To &to, const From &from) {
  return Converter::convert(to, from);
}

REQUIRE_MATH_OBJECTS(To, From) To convert(const From &from) {
  static_assert(IsConvertible<To>::value, "To must be Convertible");

  static const To to;
  auto res = convert(to, from);

  if (!res) {
    throw std::bad_cast();
  }

  return cast<To>(*res);
}

}

#undef REQUIRE_MATH_OBJECTS
