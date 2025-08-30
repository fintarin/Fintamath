#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "fintamath/core/FintamathInterfaceBody.hpp"
#include "fintamath/core/None.hpp"

namespace fintamath {

class IMathObject {
  FINTAMATH_INTERFACE_BODY(IMathObject, None)

public:
  virtual ~IMathObject() = default;

  virtual constexpr MathObjectClass getClass() const noexcept = 0;

  virtual std::string toString() const noexcept;

  virtual std::unique_ptr<IMathObject> clone() const & noexcept = 0;

  virtual std::unique_ptr<IMathObject> clone() && noexcept = 0;

  virtual std::unique_ptr<IMathObject> toMinimalObject() const noexcept;

protected:
  virtual const IMathObject &getDefaultObject() const noexcept = 0;

  virtual void registerDefaultObject() const;
};

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs);

}
