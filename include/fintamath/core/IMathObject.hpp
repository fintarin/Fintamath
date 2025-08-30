#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/InterfaceBody.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectPointers.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_INTERFACE_BODY(IMathObject, std::nullptr_t)

public:
  virtual ~IMathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

  virtual Unique<IMathObject> clone() const & noexcept = 0;

  virtual Unique<IMathObject> clone() && noexcept = 0;

  virtual Shared<IMathObject> unwrapp() const noexcept;

protected:
  virtual const IMathObject &getDefaultObject() const noexcept = 0;

  virtual void registerDefaultObject() const;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
