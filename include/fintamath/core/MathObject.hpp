#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/MathObjectBase.hpp"
#include "fintamath/core/MathObjectMacro.hpp"

namespace fintamath {

class MathObject : public MathObjectBase {
  FINTAMATH_CLASS_BODY(MathObject, MathObjectBase)

public:
  virtual std::string toString() const noexcept;

protected:
  virtual void registerDefaultObject() const;

  MathObject() = default;
};

std::ostream &operator<<(std::ostream &out, const MathObject &rhs);

}
