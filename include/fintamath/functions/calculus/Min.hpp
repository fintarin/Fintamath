#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Min final : public IFunctionCRTP<IComparable, Min, IComparable> {
public:
  std::string toString() const override {
    return "min";
  }

  static constexpr bool isVariadicStatic() {
    return true;
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Min;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Min, minExpr);

}
