#pragma once

#include <concepts>
#include <functional>
#include <memory>
#include <ranges>
#include <type_traits>

#include "fintamath/core/MathObjectTypes.hpp"

namespace fintamath {

class IMathObject;

namespace stdr = std::ranges;
namespace stdv = std::views;

template <typename From, typename To>
concept ConvertibleToAndNotSameAs = std::convertible_to<From, To> && !std::same_as<From, To>;

template <typename FromArg, typename ToArg>
concept SameAsUnqual = (std::same_as<std::remove_cvref_t<FromArg>, std::remove_cvref_t<ToArg>>);

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const From &from) {
  if constexpr (std::is_base_of_v<To, From>) {
    return true;
  }
  else if constexpr (!std::is_base_of_v<From, To>) {
    return false;
  }
  else {
    return isBaseOf(To::getTypeStatic(), from.getType());
  }
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const From *from) {
  if (!from) {
    return false;
  }

  return is<To>(*from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const std::unique_ptr<From> &from) {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const std::shared_ptr<From> &from) {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const std::shared_ptr<const From> &from) {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const std::reference_wrapper<From> &from) {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
bool is(const std::reference_wrapper<const From> &from) {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
const To &cast(const From &from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      throw std::bad_cast{};
    }
  }

  return static_cast<const To &>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
To &cast(From &from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      throw std::bad_cast{};
    }
  }

  return static_cast<To &>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
const To *cast(const From *from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      return {};
    }
  }

  return static_cast<const To *>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
To *cast(From *from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      return {};
    }
  }

  return static_cast<To *>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
std::unique_ptr<To> cast(std::unique_ptr<From> &&from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      from.reset();
      return {};
    }
  }

  From *fromRawPtr = from.release();
  auto *toRawPtr = static_cast<To *>(fromRawPtr);
  return std::unique_ptr<To>(toRawPtr);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
std::shared_ptr<const To> cast(const std::shared_ptr<const From> &from) {
  if constexpr (!std::is_base_of_v<To, From>) {
    if (!is<To>(from)) {
      return {};
    }
  }

  return std::static_pointer_cast<const To>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
std::shared_ptr<To> cast(const std::shared_ptr<From> &from) {
  return std::const_pointer_cast<To>(cast<To>(std::const_pointer_cast<const From>(from)));
}

}
