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

class Coth : public IFunctionCRTP<INumber, Coth, INumber> {
  FINTAMATH_CLASS_BODY(Coth, IFunction)

public:
  std::string toString() const override {
    return "coth";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCothSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Coth, cothExpr);

}
