#pragma once

#include "fintamath/core/MathObjectIdStorage.hpp"

#define FINTAMATH_CLASS_BODY(Class, ParentClass)    \
public:                                             \
  using Parent = ParentClass;                       \
                                                    \
  static MathObjectClass getClassStatic() noexcept; \
                                                    \
private:

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)                                        \
  MathObjectClass Class::getClassStatic() noexcept {                                 \
    static const detail::MathObjectClassData data{#Class, Parent::getClassStatic()}; \
    return &data;                                                                    \
  }

#define FINTAMATH_PARENT_CLASS_BODY(Class, ParentClass)    \
  FINTAMATH_CLASS_BODY(Class, ParentClass)                 \
                                                           \
public:                                                    \
  template <std::derived_from<Class> T>                    \
  static void registerType() {                             \
    detail::MathObjectIdStorage::add(T::getClassStatic()); \
  }                                                        \
                                                           \
private:

#define FINTAMATH_PARENT_CLASS_IMPLEMENTATION(Class) \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)

#define FINTAMATH_CHILD_CLASS_BODY(Class, ParentClass) \
  FINTAMATH_CLASS_BODY(Class, ParentClass)             \
                                                       \
public:                                                \
  MathObjectClass getClass() const noexcept override;  \
                                                       \
private:

#define FINTAMATH_CHILD_CLASS_IMPLEMENTATION(Class)  \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)              \
                                                     \
  MathObjectClass Class::getClass() const noexcept { \
    return getClassStatic();                         \
  }
