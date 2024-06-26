#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Mod : public IOperatorCRTP<INumber, Mod, INumber, INumber> {
  FINTAMATH_CLASS_BODY(Mod, IOperator)

public:
  std::string toString() const override {
    return "mod";
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Modulo;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiModSimplify(const INumber &lhs, const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Mod, modExpr);

}
