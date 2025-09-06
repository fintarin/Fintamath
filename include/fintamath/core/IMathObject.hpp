#pragma once

#include <string>

#include "fintamath/core/MathObjectMacro.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(IMathObject, None)

public:
  virtual ~IMathObject() noexcept = default;

  virtual MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
