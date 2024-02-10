#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ln final : public IFunctionCRTP<INumber, Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Ln;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiLnSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Ln, lnExpr);

}
