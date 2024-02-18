#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Neg final : public IOperatorCRTP<IArithmetic, Neg, IArithmetic> {
public:
  std::string toString() const override {
    return "-";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Neg, "Neg"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Neg, negExpr);

}
