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

class Not : public IOperatorCRTP<Boolean, Not, Boolean> {
  FINTAMATH_CLASS_BODY(Not, IOperator)

public:
  std::string toString() const override {
    return "~";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Not, notExpr);

}
