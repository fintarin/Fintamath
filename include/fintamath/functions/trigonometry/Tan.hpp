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

class Real;

class Tan final : public IFunctionCRTP<INumber, Tan, INumber> {
public:
  Tan() = default;

  std::string toString() const override {
    return "tan";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Tan;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiTanSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Tan, tanExpr);

}
