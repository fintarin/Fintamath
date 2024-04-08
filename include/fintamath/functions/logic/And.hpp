#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class And : public IFunctionCRTP<Boolean, And, Boolean> {
  FINTAMATH_CLASS_BODY(And, IFunction)

public:
  std::string toString() const override {
    return "and";
  }

  static constexpr bool isVariadicStatic() noexcept {
    return true;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(And, andExpr);

}
