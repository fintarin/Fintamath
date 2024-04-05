#pragma once

#include <concepts>
#include <functional>
#include <memory>

#include "fintamath/core/MultiMethod.hpp"

namespace fintamath {

class IMathObject;

namespace detail {

class Converter final {
  template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
  using ConverterFunction = std::function<std::unique_ptr<IMathObject>(const To &to, const From &from)>;

  using ConverterMultiMethod = MultiMethod<std::unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)>;

public:
  static std::unique_ptr<IMathObject> convert(const IMathObject &to, const IMathObject &from) noexcept {
    return getConverter()(to, from);
  }

  static bool isConvertible(const IMathObject &to, const IMathObject &from) noexcept {
    return getConverter().contains(to, from);
  }

  template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
  static void add(const ConverterFunction<To, From> &convertFunc) noexcept {
    getConverter().add<To, From>(convertFunc);
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

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool isConvertible(const To &to, const From &from) {
  return detail::Converter::isConvertible(to, from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool isConvertible(const From &from) {
  static const To to;
  return detail::Converter::isConvertible(to, from);
}

}
