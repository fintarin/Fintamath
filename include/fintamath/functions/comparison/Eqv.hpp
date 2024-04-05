#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Eqv final : public IOperatorCRTP<Boolean, Eqv, IComparable, IComparable> {
  FINTAMATH_CLASS_BODY(Eqv)

public:
  std::string toString() const noexcept override {
    return "=";
  }

  static constexpr bool isAssociativeStatic() {
    return true;
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Comparison;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Eqv, eqvExpr);

}
