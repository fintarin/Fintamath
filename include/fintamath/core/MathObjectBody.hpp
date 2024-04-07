#pragma once

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"

#define FINTAMATH_CLASS_BODY(Class)                   \
public:                                               \
  static constexpr MathObjectClass getClassStatic() { \
    return {#Class};                                  \
  }                                                   \
                                                      \
private:

#define FINTAMATH_PARENT_CLASS_BODY(Class)                      \
  FINTAMATH_CLASS_BODY(Class)                                   \
                                                                \
private:                                                        \
  using Class##Parser = detail::Parser<std::unique_ptr<Class>>; \
                                                                \
  FINTAMATH_API static Class##Parser &getParser() {             \
    FINTAMATH_API static Class##Parser parser;                  \
    return parser;                                              \
  }                                                             \
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
    MathObjectClass::bindTypes<Class, T>();                     \
    getParser().registerType<T>();                              \
  }                                                             \
                                                                \
private:

#define FINTAMATH_PARENT_CLASS_IMPLEMENTATION(Class)
