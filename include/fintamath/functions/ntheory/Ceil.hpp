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

class Ceil final : public IFunctionCRTP<INumber, Ceil, INumber> {
public:
  std::string toString() const override {
    return "ceil";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Ceil;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCeilSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Ceil, ceilExpr);

}
