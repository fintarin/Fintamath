#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Neg final : public IOperatorCRTP<IArithmetic, Neg, IArithmetic> {
  FINTAMATH_CLASS_BODY(Neg)

public:
  std::string toString() const override {
    return "-";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Neg, negExpr);

}
