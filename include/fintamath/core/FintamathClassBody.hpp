#pragma once

#include <fmt/format.h>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/FintamathInterfaceBody.hpp"
#include "fintamath/exceptions/Exception.hpp"

#define FINTAMATH_CLASS_BODY(Class, SuperClass)                  \
  FINTAMATH_INTERFACE_BODY(Class, SuperClass)                    \
                                                                 \
public:                                                          \
  constexpr MathObjectClass getClass() const noexcept override { \
    return getClassStatic();                                     \
  }                                                              \
                                                                 \
  static const Class &getDefaultObjectStatic() noexcept {        \
    return defaultObject##Class;                                 \
  }                                                              \
                                                                 \
  const Class &getDefaultObject() const noexcept override {      \
    return getDefaultObjectStatic();                             \
  }                                                              \
                                                                 \
  std::unique_ptr<IMathObject> clone() const &override {         \
    if constexpr (std::is_copy_constructible_v<Class>) {         \
      return std::make_unique<Class>(*this);                     \
    }                                                            \
    else {                                                       \
      throwUnableToCloneException();                             \
    }                                                            \
  }                                                              \
                                                                 \
  std::unique_ptr<IMathObject> clone() && override {             \
    if constexpr (std::is_copy_constructible_v<Class>) {         \
      return std::make_unique<Class>(std::move(*this));          \
    }                                                            \
    else {                                                       \
      throwUnableToCloneException();                             \
    }                                                            \
  }                                                              \
                                                                 \
private:                                                         \
  [[noreturn]] void throwUnableToCloneException() const {        \
    throw Exception(fmt::format(                                 \
      R"(Unable to clone {} as it is not copy constructible)",   \
      getClass()->getName()                                      \
    ));                                                          \
  }                                                              \
                                                                 \
private:                                                         \
  FINTAMATH_EXPORT static const Class defaultObject##Class;

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)    \
  FINTAMATH_INTERFACE_IMPLEMENTATION(Class)      \
                                                 \
  const Class Class::defaultObject##Class = [] { \
    Class object;                                \
    object.registerDefaultObject();              \
    return object;                               \
  }();
