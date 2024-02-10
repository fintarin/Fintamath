#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Not final : public IOperatorCRTP<Boolean, Not, Boolean> {
public:
  Not() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "~";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Not;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Not, notExpr);

}
