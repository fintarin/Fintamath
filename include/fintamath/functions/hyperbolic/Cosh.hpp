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

class Cosh final : public IFunctionCRTP<INumber, Cosh, INumber> {
  FINTAMATH_CLASS_BODY(Cosh)

public:
  std::string toString() const noexcept override {
    return "cosh";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCoshSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Cosh, coshExpr);

}
