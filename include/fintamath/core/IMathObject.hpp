#pragma once

#include <ostream>
#include <string>

#include "fintamath/core/FintamathInterfaceBody.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class FINTAMATH_EXPORT IMathObject {
  FINTAMATH_INTERFACE_BODY(IMathObject, None)

public:
  virtual ~IMathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

protected:
  virtual void registerDefaultObject() const;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
