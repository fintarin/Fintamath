#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Derivative : public IFunctionCRTP<IComparable, Derivative, IComparable, Variable> {
  FINTAMATH_CLASS_BODY(Derivative, IFunction)

public:
  std::string toString() const override {
    return "derivative";
  }

  static constexpr bool isEvaluatableStatic() {
    return false;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Derivative, derivativeExpr);

}
