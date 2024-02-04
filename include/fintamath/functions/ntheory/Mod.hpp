#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Mod final : public IOperatorCRTP<INumber, Mod, INumber, INumber> {
public:
  Mod() : IOperatorCRTP(Priority::Modulo) {
  }

  std::string toString() const override {
    return "mod";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Mod;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiModSimplify(const INumber &lhs, const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Mod, modExpr);

}
