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

class Impl : public IOperatorCRTP<Boolean, Impl, Boolean, Boolean> {
  FINTAMATH_CLASS_BODY(Impl, IOperator)

public:
  std::string toString() const override {
    return "->";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Implication;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Impl, implExpr);

}
