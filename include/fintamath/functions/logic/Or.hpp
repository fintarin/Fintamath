#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Or : public IFunctionCRTP<Boolean, Or, Boolean> {
  FINTAMATH_CLASS_BODY(Or, IFunction)

public:
  std::string toString() const override {
    return "or";
  }

  static constexpr bool isVariadicStatic() {
    return true;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Or, orExpr);

}
