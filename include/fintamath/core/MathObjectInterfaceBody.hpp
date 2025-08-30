#pragma once

#include "fintamath/core/MathObjectClass.hpp"

#define FINTAMATH_INTERFACE_BODY(Class, SuperClass)              \
public:                                                          \
  using Super = SuperClass;                                      \
                                                                 \
  static constexpr MathObjectClass getClassStatic() noexcept {   \
    return &classData##Class;                                    \
  }                                                              \
                                                                 \
private:                                                         \
  static constexpr detail::MathObjectClassData classData##Class{ \
    #Class,                                                      \
    SuperClass::getClassStatic()                                 \
  };                                                             \
                                                                 \
private:
