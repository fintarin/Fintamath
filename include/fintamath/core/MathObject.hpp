#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/MathObjectInterfaceBody.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class MathObject {
  FINTAMATH_INTERFACE_BODY(MathObject, None)

public:
  virtual ~MathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

protected:
  virtual void registerDefaultObject() const;
};

std::ostream &operator<<(std::ostream &out, const MathObject &rhs);

}
