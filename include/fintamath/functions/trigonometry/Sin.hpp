#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Sin final : public IFunctionCRTP<INumber, Sin, INumber> {
public:
  std::string toString() const override {
    return "sin";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Sin, "Sin"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSinSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sin, sinExpr);

}
