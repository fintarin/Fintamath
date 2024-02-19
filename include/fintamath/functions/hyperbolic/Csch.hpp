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

class Csch final : public IFunctionCRTP<INumber, Csch, INumber> {
public:
  std::string toString() const override {
    return "csch";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Csch, "Csch"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCschSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Csch, cschExpr);

}
