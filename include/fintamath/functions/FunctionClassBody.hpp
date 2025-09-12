#pragma once

#include "fintamath/core/ClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)          \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                         \
protected:                                                        \
  Class() = default;                                              \
                                                                  \
public:                                                           \
  explicit Class(Arguments inArgs);                               \
                                                                  \
  const Declaration &getDeclaration() const noexcept override;    \
                                                                  \
  static const Declaration &getDeclarationStatic() noexcept;      \
                                                                  \
protected:                                                        \
  SharedRef<IFunction> makeSelf(Arguments inArgs) const override; \
                                                                  \
private:                                                          \
  FINTAMATH_EXPORT static const Declaration declaration##Class;

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, ...)              \
  const IFunction::Declaration Class::declaration##Class = __VA_ARGS__;  \
                                                                         \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)                                  \
                                                                         \
  Class::Class(Arguments inArgs)                                         \
      : Super(getDeclarationStatic(), std::move(inArgs)) {}              \
                                                                         \
  const IFunction::Declaration &Class::getDeclaration() const noexcept { \
    return declaration##Class;                                           \
  }                                                                      \
                                                                         \
  const IFunction::Declaration &Class::getDeclarationStatic() noexcept { \
    return declaration##Class;                                           \
  }                                                                      \
                                                                         \
  SharedRef<IFunction> Class::makeSelf(Arguments inArgs) const {         \
    return makeShared<Class>(std::move(inArgs));                         \
  }
