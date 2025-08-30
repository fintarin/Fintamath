#pragma once

#include <concepts>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class IMathObject;

namespace detail {

class Converter final {
  using ConverterMultiMethod = MultiMethod<Shared<IMathObject>(const IMathObject &, const IMathObject &)>;

public:
  static Shared<IMathObject> convert(const IMathObject &to, const IMathObject &from);

  template <typename To, typename From>
  static void add() {
    getConverter().add<To, From>([](const To & /*to*/, const From &from) {
      return makeShared<To>(from);
    });
  }

private:
  static ConverterMultiMethod &getConverter();
};

}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
Shared<To> convert(const To &to, const From &from) {
  return cast<To>(detail::Converter::convert(to, from));
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
Shared<To> convert(const From &from) {
  static const To to;
  return convert(to, from);
}

}
