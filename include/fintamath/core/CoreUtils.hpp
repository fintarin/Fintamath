#pragma once

#include <memory>

#include "fintamath/core/CoreTraits.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/meta/Converter.hpp"

#define REQUIRE_MATH_OBJECTS(To, From)                                                                                 \
  template <typename To, typename From,                                                                                \
            typename = std::enable_if_t<std::is_base_of_v<IMathObject, To> && std::is_base_of_v<IMathObject, From>>>

namespace fintamath {

REQUIRE_MATH_OBJECTS(To, From) bool is(const From &from) {
  if constexpr (std::is_base_of_v<To, From>) {
    return true;
  }
  else if constexpr (!std::is_base_of_v<From, To>) {
    return false;
  }
  else {
    return isBaseOf(To::getTypeIdStatic(), from.getTypeId());
  }
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const From *from) {
  if (!from) {
    return false;
  }

  return is<To>(*from);
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const std::unique_ptr<From> &from) {
  return is<To>(from.get());
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const std::shared_ptr<From> &from) {
  return is<To>(from.get());
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const std::shared_ptr<const From> &from) {
  return is<To>(from.get());
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const std::reference_wrapper<From> &from) {
  return is<To>(from.get());
}

REQUIRE_MATH_OBJECTS(To, From) bool is(const std::reference_wrapper<const From> &from) {
  return is<To>(from.get());
}

REQUIRE_MATH_OBJECTS(To, From) To &cast(From &from) {
  if (!is<To>(from)) {
    throw std::bad_cast();
  }

  return static_cast<To &>(from);
}

REQUIRE_MATH_OBJECTS(To, From) const To &cast(const From &from) {
  if (!is<To>(from)) {
    throw std::bad_cast();
  }

  return static_cast<const To &>(from);
}

REQUIRE_MATH_OBJECTS(To, From) To *cast(From *from) {
  if (!is<To>(from)) {
    return {};
  }

  return static_cast<To *>(from);
}

REQUIRE_MATH_OBJECTS(To, From) const To *cast(const From *from) {
  if (!is<To>(from)) {
    return {};
  }

  return static_cast<const To *>(from);
}

REQUIRE_MATH_OBJECTS(To, From) To &&cast(IMathObject &&from) {
  if (!is<To>(from)) {
    return {};
  }

  return static_cast<To &&>(from);
}

REQUIRE_MATH_OBJECTS(To, From) std::unique_ptr<To> cast(std::unique_ptr<From> &&from) {
  if (!is<To>(from)) {
    from.reset();
    return {};
  }

  From *fromRawPtr = from.release();
  auto *toRawPtr = static_cast<To *>(fromRawPtr);
  return std::unique_ptr<To>(toRawPtr);
}

REQUIRE_MATH_OBJECTS(To, From) std::shared_ptr<To> cast(const std::shared_ptr<From> &from) {
  if (!is<To>(from)) {
    return std::shared_ptr<To>();
  }

  return std::static_pointer_cast<To>(from);
}

REQUIRE_MATH_OBJECTS(To, From) std::shared_ptr<const To> cast(const std::shared_ptr<const From> &from) {
  if (!is<To>(from)) {
    return std::shared_ptr<const To>();
  }

  return std::static_pointer_cast<const To>(from);
}

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
