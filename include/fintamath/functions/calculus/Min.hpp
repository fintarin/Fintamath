#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Min : public IFunctionCRTP<IComparable, Min, IComparable> {
  FINTAMATH_CLASS_BODY(Min, IFunction)

public:
  std::string toString() const override {
    return "min";
  }

  static constexpr bool isVariadicStatic() noexcept {
    return true;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Min, minExpr);

}
