#pragma once

#include "fintamath/core/MathObjectClass.hpp"

#define FINTAMATH_CLASS_BODY(Class, SuperClass)                  \
  FINTAMATH_INTERFACE_BODY(Class, SuperClass)                    \
                                                                 \
public:                                                          \
  constexpr MathObjectClass getClass() const noexcept override { \
    return getClassStatic();                                     \
  }                                                              \
                                                                 \
  static const Class &getDefaultObject() noexcept {              \
    return defaultObject##Class;                                 \
  }                                                              \
                                                                 \
private:                                                         \
  static const Class defaultObject##Class;

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)    \
  FINTAMATH_INTERFACE_IMPLEMENTATION(Class)      \
                                                 \
  const Class Class::defaultObject##Class = [] { \
    Class object;                                \
    object.registerDefaultObject();              \
    return object;                               \
  }();
