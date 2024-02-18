#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sqrt final : public IFunctionCRTP<INumber, Sqrt, INumber> {
public:
  std::string toString() const override {
    return "sqrt";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Sqrt, "Sqrt"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Sqrt, sqrtExpr);

}
