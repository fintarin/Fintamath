#pragma once

#include <ostream>
#include <string>

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

  virtual UniqueRef<IMathObject> clone() const & noexcept = 0;

  virtual UniqueRef<IMathObject> clone() && noexcept = 0;

  virtual SharedPtr<IMathObject> unwrapp() const noexcept;

  friend bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) noexcept;

protected:
  virtual bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept = 0;

  virtual const IMathObject &getDefaultObject() const noexcept = 0;

  virtual void registerDefaultObject() const;
};

bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) noexcept;

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
