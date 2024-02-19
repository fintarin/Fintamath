#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Max final : public IFunctionCRTP<IComparable, Max, IComparable> {
public:
  std::string toString() const override {
    return "max";
  }

  static constexpr bool isVariadicStatic() {
    return true;
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Max, "Max"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Max, maxExpr);

}
