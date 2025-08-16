#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Qualifiers.hpp"

namespace fintamath {

class IMathObject;

constexpr bool is(const MathObjectClass to, const MathObjectClass from) noexcept {
  return from && from->is(to);
}

template <std::derived_from<IMathObject> To>
constexpr bool is(const MathObjectClass from) noexcept {
  return is(To::getClassStatic(), from);
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
  requires(std::is_base_of_v<IMathObject, typename detail::RemoveQualifiers<From>::element_type>)
inline bool is(const From &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, typename From>
  requires(std::is_base_of_v<IMathObject, typename detail::RemoveQualifiers<From>>)
inline decltype(auto) cast(From &&from) noexcept {
  using ResultType = detail::CopyQualifiersFromToType<From, To>;

  assert(is<To>(from));

  return static_cast<ResultType>(std::forward<From>(from));
}

template <std::derived_from<IMathObject> To, typename From>
  requires(std::is_base_of_v<IMathObject, typename detail::RemoveQualifiers<From>>)
inline decltype(auto) cast(From *from) noexcept {
  using ResultType = detail::CopyQualifiersFromToType<From, To>;

  if (!is<To>(from)) {
    return static_cast<ResultType *>(nullptr);
  }

  return static_cast<ResultType *>(from);
}

template <std::derived_from<IMathObject> To, typename From>
  requires(std::is_base_of_v<IMathObject, typename detail::RemoveQualifiers<From>::element_type>)
inline decltype(auto) cast(From &&from) noexcept {
  using ResultType = detail::CopyQualifiersFromToType<typename detail::RemoveQualifiers<From>::element_type, To>;

  if (!is<To>(from)) {
    return std::shared_ptr<ResultType>();
  }

  return std::static_pointer_cast<ResultType>(std::forward<From>(from));
}

}
