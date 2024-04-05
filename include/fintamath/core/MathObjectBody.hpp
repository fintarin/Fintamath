#pragma once

#include <memory>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"

#define FINTAMATH_CLASS_BODY(Class)                            \
public:                                                        \
  static constexpr MathObjectClass getClassStatic() noexcept { \
    return {#Class};                                           \
  }                                                            \
                                                               \
private:

#define FINTAMATH_PARENT_CLASS_BODY(Class)                      \
  FINTAMATH_CLASS_BODY(Class)                                   \
                                                                \
private:                                                        \
  using Class##Parser = detail::Parser<std::unique_ptr<Class>>; \
                                                                \
  static Class##Parser &getParser() noexcept;                   \
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
  static void registerType() noexcept {                         \
    MathObjectClass::bindTypes<Class, T>();                     \
    getParser().template registerType<T>();                     \
  }                                                             \
                                                                \
private:

#define FINTAMATH_PARENT_CLASS_IMPLEMENTATION(Class)  \
  Class::Class##Parser &Class::getParser() noexcept { \
    static Class##Parser parser;                      \
    return parser;                                    \
  }
