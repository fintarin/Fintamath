#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Tan : public IFunctionCRTP<INumber, Tan, INumber> {
  FINTAMATH_CLASS_BODY(Tan, IFunction)

public:
  std::string toString() const override {
    return "tan";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiTanSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Tan, tanExpr);

}
