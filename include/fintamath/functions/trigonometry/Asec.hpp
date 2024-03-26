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

class Asec final : public IFunctionCRTP<INumber, Asec, INumber> {
  FINTAMATH_CLASS_BODY(Asec)

public:
  std::string toString() const override {
    return "asec";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAsecSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Asec, asecExpr);

}
