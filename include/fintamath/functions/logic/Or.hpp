#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Or final : public IOperatorCRTP<Boolean, Or, Boolean, Boolean> {
  FINTAMATH_CLASS_BODY(Or)

public:
  std::string toString() const noexcept override {
    return "|";
  }

  static constexpr bool isAssociativeStatic() {
    return true;
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Disjunction;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Or, orExpr);

}
