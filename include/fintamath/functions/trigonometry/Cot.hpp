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

class Cot final : public IFunctionCRTP<INumber, Cot, INumber> {
  FINTAMATH_CLASS_BODY(Cot)

public:
  std::string toString() const noexcept override {
    return "cot";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCotSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Cot, cotExpr);

}
