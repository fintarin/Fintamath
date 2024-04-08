#pragma once

#include <memory>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectIdStorage.hpp"
#include "fintamath/core/Parser.hpp"

#define FINTAMATH_CLASS_BODY(Class, ParentClass)    \
public:                                             \
  using Parent = ParentClass;                       \
                                                    \
  static MathObjectClass getClassStatic() noexcept; \
                                                    \
private:

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)        \
  MathObjectClass Class::getClassStatic() noexcept { \
    static const detail::MathObjectClassImpl         \
        classImpl{#Class, Parent::getClassStatic()}; \
    return &classImpl;                               \
  }

#define FINTAMATH_PARENT_CLASS_BODY(Class, ParentClass)         \
  FINTAMATH_CLASS_BODY(Class, ParentClass)                      \
                                                                \
private:                                                        \
  using Class##Parser = detail::Parser<std::unique_ptr<Class>>; \
                                                                \
  static Class##Parser &getParser();                            \
                                                                \
public:                                                         \
  static auto parse(std::string str) {                          \
    return getParser().parse(std::move(str));                   \
  }                                                             \
                                                                \
  static auto parseFirst(std::string str) {                     \
    return getParser().parseFirst(std::move(str));              \
  }                                                             \
                                                                \
  template <std::derived_from<Class> T>                         \
  static void registerType() {                                  \
    MathObjectIdStorage::add(T::getClassStatic());              \
    getParser().registerType<T>();                              \
  }                                                             \
                                                                \
private:

#define FINTAMATH_PARENT_CLASS_IMPLEMENTATION(Class) \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)              \
                                                     \
  Class::Class##Parser &Class::getParser() {         \
    static Class##Parser parser;                     \
    return parser;                                   \
  }
