#pragma once

#include <fmt/format.h>

#include "fintamath/core/FintamathClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)                \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                               \
                                                                        \
protected:                                                              \
  std::unique_ptr<IFunction> makeSelf(Arguments inArgs) const override; \
                                                                        \
private:

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class)                 \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)                                \
                                                                       \
  std::unique_ptr<IFunction> Class::makeSelf(Arguments inArgs) const { \
    return Class::make(std::move(inArgs));                             \
  }
