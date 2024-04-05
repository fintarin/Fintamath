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

class Acsch final : public IFunctionCRTP<INumber, Acsch, INumber> {
  FINTAMATH_CLASS_BODY(Acsch)

public:
  std::string toString() const noexcept override {
    return "acsch";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcschSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acsch, acschExpr);

}
