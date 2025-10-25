#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/InterfaceBody.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Pointers.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_INTERFACE_BODY(IMathObject, std::nullptr_t)

public:
  virtual ~IMathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

  virtual UniqueRef<IMathObject> cloneSelf() const & noexcept = 0;

  virtual UniqueRef<IMathObject> cloneSelf() && noexcept = 0;

  virtual SharedPtr<IMathObject> unwrappSelf() const noexcept;

  template <typename T>
  friend UniqueRef<IMathObject> clone(T &&arg);

  template <typename T>
  friend SharedRef<IMathObject> unwrapp(T &&arg);

  friend bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) noexcept;

protected:
  virtual bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept = 0;

  virtual const IMathObject &getDefaultObject() const noexcept = 0;

  virtual void registerDefaultObject() const;
};

bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) noexcept;

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

template <typename T>
UniqueRef<IMathObject> clone(T &&arg) {
  if constexpr (detail::IsSmartReference<T>) {
    return std::forward<T>(arg)->cloneSelf();
  }
  else {
    return std::forward<T>(arg).cloneSelf();
  }
}

template <typename T>
SharedRef<IMathObject> unwrapp(T &&arg) {
  if constexpr (detail::IsSmartReference<T>) {
    if (auto unwrapped = arg->unwrappSelf()) {
      return unwrapped.toRef();
    }

    return std::forward<T>(arg);
  }
  else {
    if (auto unwrapped = arg.unwrappSelf()) {
      return unwrapped.toRef();
    }

    return std::forward<T>(arg).cloneSelf();
  }
}

}
