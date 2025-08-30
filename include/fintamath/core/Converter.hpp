#pragma once

#include <concepts>
#include <memory>

#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class IMathObject;

namespace detail {

class Converter final {
  using ConverterMultiMethod = MultiMethod<std::unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)>;

public:
  static std::unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from);

  template <typename To, typename From>
  static void add(auto convertFunc) {
    getConverter().add<To, From>([convertFunc = std::move(convertFunc)](const To & /*to*/, const From &from) {
      return convertFunc(from);
    });
  }

private:
  static ConverterMultiMethod &getConverter();
};

}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
std::unique_ptr<To> convert(const To &to, const From &from) {
  return cast<To>(detail::Converter::convert(to, from));
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
std::unique_ptr<To> convert(const From &from) {
  static const To to;
  return convert(to, from);
}

}
