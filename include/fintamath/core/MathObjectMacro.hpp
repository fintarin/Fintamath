#pragma once

#include "fintamath/core/MathObjectIdStorage.hpp"

#define FINTAMATH_CLASS_BODY(Class, SuperClass)               \
public:                                                       \
  using Super = SuperClass;                                   \
                                                              \
  static MathObjectClass getClassStatic() noexcept;           \
                                                              \
  virtual MathObjectClass getClass() const noexcept override; \
                                                              \
private:                                                      \
  static const Class defaultObject##Class;

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)                                       \
  const Class Class::defaultObject##Class = [] {                                    \
    Class object;                                                                   \
    object.registerDefaultObject();                                                 \
    return object;                                                                  \
  }();                                                                              \
                                                                                    \
  MathObjectClass Class::getClassStatic() noexcept {                                \
    static const detail::MathObjectClassData data{#Class, Super::getClassStatic()}; \
    return &data;                                                                   \
  }                                                                                 \
                                                                                    \
  MathObjectClass Class::getClass() const noexcept {                                \
    return getClassStatic();                                                        \
  }
