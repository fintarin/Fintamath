#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/MathObjectInterfaceBody.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_INTERFACE_BODY(MathObject, None)

public:
  virtual ~IMathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

protected:
  virtual void registerDefaultObject() const;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
