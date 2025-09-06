#pragma once

#include "fintamath/core/FintamathExport.hpp"

#define FINTAMATH_INTERFACE_BODY(Class, SuperClass)                                \
  static_assert(std::is_object_v<Class>);                                          \
                                                                                   \
public:                                                                            \
  using Super = SuperClass;                                                        \
                                                                                   \
  static constexpr MathObjectClass getClassStatic() noexcept {                     \
    return &classData##Class;                                                      \
  }                                                                                \
                                                                                   \
private:                                                                           \
  FINTAMATH_EXPORT static constexpr detail::MathObjectClassData classData##Class = \
    detail::getClassData<Super>(#Class);

#define FINTAMATH_INTERFACE_IMPLEMENTATION(Class) \
  static_assert(std::is_object_v<Class>);         \
                                                  \
  constexpr detail::MathObjectClassData Class::classData##Class;
