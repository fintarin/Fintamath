#pragma once

#include "fintamath/core/InterfaceBody.hpp"

#define FINTAMATH_CLASS_BODY(Class, SuperClass)                   \
  FINTAMATH_INTERFACE_BODY(Class, SuperClass)                     \
                                                                  \
public:                                                           \
  constexpr MathObjectClass getClass() const noexcept override {  \
    return getClassStatic();                                      \
  }                                                               \
                                                                  \
  std::unique_ptr<IMathObject> clone() const & noexcept override; \
                                                                  \
  std::unique_ptr<IMathObject> clone() && noexcept override;      \
                                                                  \
protected:                                                        \
  const Class &getDefaultObject() const noexcept override;        \
                                                                  \
private:                                                          \
  FINTAMATH_EXPORT static const Class defaultObject##Class;

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)                    \
  FINTAMATH_INTERFACE_IMPLEMENTATION(Class)                      \
                                                                 \
  const Class Class::defaultObject##Class = [] {                 \
    Class object;                                                \
    object.registerDefaultObject();                              \
    return object;                                               \
  }();                                                           \
                                                                 \
  std::unique_ptr<IMathObject> Class::clone() const & noexcept { \
    return std::make_unique<Class>(*this);                       \
  }                                                              \
                                                                 \
  std::unique_ptr<IMathObject> Class::clone() && noexcept {      \
    return std::make_unique<Class>(std::move(*this));            \
  }                                                              \
                                                                 \
  const Class &Class::getDefaultObject() const noexcept {        \
    return defaultObject##Class;                                 \
  }
