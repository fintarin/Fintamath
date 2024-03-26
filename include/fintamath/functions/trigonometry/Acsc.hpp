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

class Acsc final : public IFunctionCRTP<INumber, Acsc, INumber> {
  FINTAMATH_CLASS_BODY(Acsc)

public:
  std::string toString() const override {
    return "acsc";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcscSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acsc, acscExpr);

}
