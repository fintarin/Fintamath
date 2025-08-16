#pragma once

#include "fintamath/core/ClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)                \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                               \
                                                                        \
public:                                                                 \
  const Declaration &getDeclaration() const noexcept override;          \
                                                                        \
protected:                                                              \
  std::unique_ptr<IFunction> makeSelf(Arguments inArgs) const override; \
                                                                        \
private:                                                                \
  FINTAMATH_EXPORT static const Declaration declaration##Class;

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, ...)              \
  const IFunction::Declaration Class::declaration##Class = __VA_ARGS__;  \
                                                                         \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)                                  \
                                                                         \
  const IFunction::Declaration &Class::getDeclaration() const noexcept { \
    return declaration##Class;                                           \
  }                                                                      \
                                                                         \
  std::unique_ptr<IFunction> Class::makeSelf(Arguments inArgs) const {   \
    return make(std::move(inArgs));                                      \
  }
