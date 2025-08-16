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
  static const Class &getDefaultObjectStatic() noexcept {        \
    return defaultObject##Class;                                 \
  }                                                              \
                                                                 \
  const Class &getDefaultObject() const noexcept override {      \
    return getDefaultObjectStatic();                             \
  }                                                              \
                                                                 \
  std::unique_ptr<IMathObject> clone() const noexcept override { \
    return std::make_unique<Class>(*this);                       \
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
