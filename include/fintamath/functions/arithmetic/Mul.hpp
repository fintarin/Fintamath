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

class Mul final : public IOperatorCRTP<IArithmetic, Mul, IArithmetic, IArithmetic> {
  FINTAMATH_CLASS_BODY(Mul)

public:
  std::string toString() const noexcept override {
    return "*";
  }

  static constexpr bool isAssociativeStatic() {
    return true;
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Multiplication;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Mul, mulExpr);

}
