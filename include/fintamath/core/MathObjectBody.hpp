#pragma once

#include <memory>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectIdStorage.hpp"
#include "fintamath/core/Parser.hpp"

#define FINTAMATH_CLASS_BODY(Class, Parent)                    \
public:                                                        \
  static constexpr MathObjectClass getClassStatic() noexcept { \
    return &objClass;                                          \
  }                                                            \
                                                               \
private:                                                       \
  static constexpr detail::MathObjectClassImpl                 \
      objClass{#Class, Parent::getClassStatic()};

#define FINTAMATH_PARENT_CLASS_BODY(Class, Parent)              \
  FINTAMATH_CLASS_BODY(Class, Parent)                           \
                                                                \
private:                                                        \
  using Class##Parser = detail::Parser<std::unique_ptr<Class>>; \
                                                                \
  static Class##Parser &getParser() noexcept;                   \
                                                                \
public:                                                         \
  static auto parse(std::string str) noexcept {                 \
    return getParser().parse(std::move(str));                   \
  }                                                             \
                                                                \
  static auto parseFirst(std::string str) noexcept {            \
    return getParser().parseFirst(std::move(str));              \
  }                                                             \
                                                                \
  template <std::derived_from<Class> T>                         \
  static void registerType() noexcept {                         \
    MathObjectIdStorage::add(T::getClassStatic());              \
    getParser().registerType<T>();                              \
  }                                                             \
                                                                \
private:

#define FINTAMATH_PARENT_CLASS_IMPLEMENTATION(Class)  \
  Class::Class##Parser &Class::getParser() noexcept { \
    static Class##Parser parser;                      \
    return parser;                                    \
  }
