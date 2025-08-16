#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class IMathObject;

template <typename T, typename... Args>
std::unique_ptr<T> makeObject(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

constexpr bool is(const MathObjectClass to, const MathObjectClass from) noexcept {
  for (MathObjectClass parent = from; parent; parent = parent->getParent()) {
    if (parent == to) {
      return true;
    }
  }

  return false;
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const From &from) noexcept {
  if constexpr (std::is_base_of_v<To, From>) {
    return true;
  }
  else if constexpr (!std::is_base_of_v<From, To>) {
    return false;
  }
  else {
    return is(To::getClassStatic(), from.getClass());
  }
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const From *from) noexcept {
  return from && is<To>(*from);
}

template <std::derived_from<IMathObject> To, typename From>
  requires std::derived_from<IMathObject, typename detail::RemoveQualifiers<From>::element_type>
inline bool is(const From &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, typename From>
  requires std::derived_from<IMathObject, typename detail::RemoveQualifiers<From>>
inline decltype(auto) cast(From &&from) noexcept {
  using ResultType = detail::CopyQualifiersFromToType<From, To>;

  if (!is<To>(from)) {
    if constexpr (std::is_pointer<From>()) {
      return ResultType{};
    }
    else {
      assert(false);
    }
  }

  return static_cast<ResultType>(std::forward<From>(from));
}

template <std::derived_from<IMathObject> To, typename From>
  requires std::derived_from<IMathObject, typename detail::RemoveQualifiers<From>::element_type>
inline decltype(auto) cast(From &&from) noexcept {
  using ResultType = detail::CopyQualifiersFromToType<typename detail::RemoveQualifiers<From>::element_type, To>;

  if (!is<To>(from)) {
    return std::shared_ptr<ResultType>();
  }

  return std::static_pointer_cast<ResultType>(std::forward<From>(from));
}

}
