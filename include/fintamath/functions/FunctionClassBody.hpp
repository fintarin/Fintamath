#pragma once

#include "fintamath/core/ClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)          \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                         \
                                                                  \
protected:                                                        \
  Class() = default;                                              \
                                                                  \
public:                                                           \
  explicit Class(Args inArgs);                                    \
                                                                  \
  explicit Class(ArgSpan inArgs);                                 \
                                                                  \
  const Declaration &getDeclaration() const noexcept override;    \
                                                                  \
  static const Declaration &getDeclarationStatic() noexcept;      \
                                                                  \
protected:                                                        \
  SharedRef<IFunction> makeSelf(ArgVector inArgs) const override; \
                                                                  \
  SharedRef<IFunction> makeSelf(ArgSpan inArgs) const override;   \
                                                                  \
private:                                                          \
  FINTAMATH_EXPORT static const Declaration declaration##Class;

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, ...)              \
  const IFunction::Declaration Class::declaration##Class = __VA_ARGS__;  \
                                                                         \
  FINTAMATH_CLASS_IMPLEMENTATION(Class)                                  \
                                                                         \
  Class::Class(Args inArgs)                                              \
      : Super(getDeclarationStatic(), std::move(inArgs)) {}              \
                                                                         \
  Class::Class(ArgSpan inArgs)                                           \
      : Super(getDeclarationStatic(), inArgs) {}                         \
                                                                         \
  const IFunction::Declaration &Class::getDeclaration() const noexcept { \
    return declaration##Class;                                           \
  }                                                                      \
                                                                         \
  const IFunction::Declaration &Class::getDeclarationStatic() noexcept { \
    return declaration##Class;                                           \
  }                                                                      \
                                                                         \
  SharedRef<IFunction> Class::makeSelf(ArgVector inArgs) const {         \
    return makeShared<Class>(std::move(inArgs));                         \
  }                                                                      \
                                                                         \
  SharedRef<IFunction> Class::makeSelf(ArgSpan inArgs) const {           \
    return makeShared<Class>(inArgs);                                    \
  }
