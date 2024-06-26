#pragma once

#include <cassert>
#include <concepts>
#include <functional>
#include <memory>
#include <type_traits>

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class IMathObject;

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
  if (!from) {
    return false;
  }

  return is<To>(*from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const std::unique_ptr<From> &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const std::shared_ptr<From> &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const std::shared_ptr<const From> &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const std::reference_wrapper<From> &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline bool is(const std::reference_wrapper<const From> &from) noexcept {
  return is<To>(from.get());
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline const To &cast(const From &from) noexcept {
  assert(is<To>(from));
  return static_cast<const To &>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline To &cast(From &from) noexcept {
  assert(is<To>(from));
  return static_cast<To &>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline const To *cast(const From *from) noexcept {
  if (!is<To>(from)) {
    return {};
  }

  return static_cast<const To *>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline To *cast(From *from) noexcept {
  if (!is<To>(from)) {
    return {};
  }

  return static_cast<To *>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline std::unique_ptr<To> cast(std::unique_ptr<From> &&from) noexcept {
  if (!is<To>(from)) {
    from.reset();
    return {};
  }

  From *fromRawPtr = from.release();
  auto *toRawPtr = static_cast<To *>(fromRawPtr);
  return std::unique_ptr<To>(toRawPtr);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline std::shared_ptr<const To> cast(const std::shared_ptr<const From> &from) noexcept {
  if (!is<To>(from)) {
    return {};
  }

  return std::static_pointer_cast<const To>(from);
}

template <std::derived_from<IMathObject> To, std::derived_from<IMathObject> From>
inline std::shared_ptr<To> cast(const std::shared_ptr<From> &from) noexcept {
  if (!is<To>(from)) {
    return {};
  }

  return std::static_pointer_cast<To>(from);
}

template <typename Comparator>
struct ToStringComparator {
  template <typename T>
  bool operator()(const T &lhs, const T &rhs) const noexcept {
    return Comparator{}(lhs.toString(), rhs.toString());
  }
};

}
