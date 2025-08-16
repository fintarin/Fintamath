#pragma once

#include <memory>

#include "fintamath/literals/Literal.hpp"

namespace fintamath {

class Constant : public Literal {
  FINTAMATH_INTERFACE_BODY(Constant, Literal)

public:
  virtual MathObjectClass getValueClass() const noexcept = 0;

  virtual std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept = 0;

  std::string toString() const noexcept override;
};

}
