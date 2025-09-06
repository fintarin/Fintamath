#pragma once

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : public ILiteral {
  FINTAMATH_CLASS_BODY(IConstant, ILiteral)

public:
  virtual MathObjectClass getValueClass() const noexcept;

  virtual std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept;

  virtual std::string getName() const noexcept;

  std::string toString() const noexcept final;
};

}
