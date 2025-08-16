#pragma once

#include "fintamath/core/ClassBody.hpp"

#define FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)       \
  FINTAMATH_CLASS_BODY(Class, SuperClass)                      \
                                                               \
public:                                                        \
  const Declaration &getDeclaration() const noexcept override; \
                                                               \
protected:                                                     \
  Shared<IFunction> makeSelf(Arguments inArgs) const override; \
                                                               \
private:                                                       \
  FINTAMATH_EXPORT static const Declaration declaration##Class;

#define FINTAMATH_FUNCTION_CLASS_BODY_WITH_MAKE(Class, SuperClass) \
  FINTAMATH_FUNCTION_CLASS_BODY(Class, SuperClass)                 \
public:                                                            \
  static Shared<Class> make(Arguments inArgs);                     \
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
  Shared<IFunction> Class::makeSelf(Arguments inArgs) const {            \
    return make(std::move(inArgs));                                      \
  }

#define FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(Class, ...) \
  FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(Class, __VA_ARGS__)         \
                                                                      \
  Shared<Class> Class::make(Arguments inArgs) {                       \
    Class self;                                                       \
    self.initSelf(std::move(inArgs));                                 \
    return makeShared<Class>(self);                                   \
  }
