#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Percent : public IOperatorCRTP<INumber, Percent, INumber> {
  FINTAMATH_CLASS_BODY(Percent, IOperator)

public:
  std::string toString() const override {
    return "%";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PostfixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Percent, percentExpr);

}
