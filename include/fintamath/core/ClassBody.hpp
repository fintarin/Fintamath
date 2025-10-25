#pragma once

#include "fintamath/core/InterfaceBody.hpp"

#define FINTAMATH_CLASS_BODY(Class, SuperClass)                  \
  FINTAMATH_INTERFACE_BODY(Class, SuperClass)                    \
                                                                 \
public:                                                          \
  constexpr MathObjectClass getClass() const noexcept override { \
    return getClassStatic();                                     \
  }                                                              \
                                                                 \
  UniqueRef<IMathObject> cloneSelf() const & noexcept override;  \
                                                                 \
  UniqueRef<IMathObject> cloneSelf() && noexcept override;       \
                                                                 \
protected:                                                       \
  const Class &getDefaultObject() const noexcept override;       \
                                                                 \
private:                                                         \
  FINTAMATH_EXPORT static const Class defaultObject##Class;

#define FINTAMATH_CLASS_IMPLEMENTATION(Class)                  \
  FINTAMATH_INTERFACE_IMPLEMENTATION(Class)                    \
                                                               \
  const Class Class::defaultObject##Class = [] {               \
    Class object;                                              \
    object.registerDefaultObject();                            \
    return object;                                             \
  }();                                                         \
                                                               \
  UniqueRef<IMathObject> Class::cloneSelf() const & noexcept { \
    return makeUnique<Class>(*this);                           \
  }                                                            \
                                                               \
  UniqueRef<IMathObject> Class::cloneSelf() && noexcept {      \
    return makeUnique<Class>(std::move(*this));                \
  }                                                            \
                                                               \
  const Class &Class::getDefaultObject() const noexcept {      \
    return defaultObject##Class;                               \
  }
