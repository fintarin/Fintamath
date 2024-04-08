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

class Max : public IFunctionCRTP<IComparable, Max, IComparable> {
  FINTAMATH_CLASS_BODY(Max, IFunction)

public:
  std::string toString() const override {
    return "max";
  }

  static constexpr bool isVariadicStatic() noexcept {
    return true;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Max, maxExpr);

}
