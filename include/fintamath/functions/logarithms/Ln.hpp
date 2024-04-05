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

class Ln final : public IFunctionCRTP<INumber, Ln, INumber> {
  FINTAMATH_CLASS_BODY(Ln)

public:
  std::string toString() const noexcept override {
    return "ln";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiLnSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Ln, lnExpr);

}
