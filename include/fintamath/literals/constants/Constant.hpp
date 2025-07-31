#pragma once

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/Literal.hpp"

namespace fintamath {

class Constant : public Literal {
  FINTAMATH_CLASS_BODY(Constant, Literal)

public:
  virtual MathObjectClass getValueClass() const noexcept;

  virtual std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept;

  virtual std::string getName() const noexcept;

  std::string toString() const noexcept final;
};

}
