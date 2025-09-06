#pragma once

#include "fintamath/core/ClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)          \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                         \
protected:                                                        \
  Class() = default;                                              \
                                                                  \
public:                                                           \
  const Declaration &getDeclaration() const noexcept override;    \
                                                                  \
  static const Declaration &getDeclarationStatic() noexcept;      \
                                                                  \
protected:                                                        \
  SharedRef<IFunction> makeSelf(Arguments inArgs) const override; \
                                                                  \
private:                                                          \
  FINTAMATH_EXPORT static const Declaration declaration##Class;

#define FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Class, SuperClass) \
  FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)                 \
                                                                   \
protected:                                                         \
  explicit Class(Arguments inArgs);                                \
                                                                   \
public:                                                            \
  static SharedRef<Class> make(Arguments inArgs);                  \
                                                                   \
private:

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, ...)              \
  const IFunction::Declaration Class::declaration##Class = __VA_ARGS__;  \
                                                                         \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)                                  \
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
    return make(std::move(inArgs));                                      \
  }

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(Class, ...)                  \
  FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, __VA_ARGS__)                          \
                                                                                       \
  Class::Class(Arguments inArgs) : Super(getDeclarationStatic(), std::move(inArgs)) {} \
                                                                                       \
  SharedRef<Class> Class::make(Arguments inArgs) {                                     \
    return makeShared<Class>(Class(std::move(inArgs)));                                \
  }
