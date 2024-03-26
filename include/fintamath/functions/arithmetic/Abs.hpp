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

class Abs final : public IFunctionCRTP<INumber, Abs, INumber> {
  FINTAMATH_CLASS_BODY(Abs)

public:
  std::string toString() const override {
    return "abs";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAbsSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Abs, absExpr);

}
