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

class Acoth final : public IFunctionCRTP<INumber, Acoth, INumber> {
  FINTAMATH_CLASS_BODY(Acoth)

public:
  std::string toString() const noexcept override {
    return "acoth";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcothSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acoth, acothExpr);

}
