#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Deg final : public IOperatorCRTP<INumber, Deg, INumber> {
public:
  std::string toString() const override {
    return "deg";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PostfixUnary;
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Deg, "Deg"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Deg, degExpr);

}
