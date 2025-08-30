#pragma once

#include <string>

#include "fintamath/core/MathObjectMacro.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_CLASS_BODY(IMathObject, None)

public:
  virtual ~IMathObject() noexcept = default;

  virtual std::string toString() const noexcept;

protected:
  virtual void registerDefaultObject() const;

  IMathObject() = default;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
