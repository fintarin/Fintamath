#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Impl final : public IOperatorCRTP<Boolean, Impl, Boolean, Boolean> {
public:
  std::string toString() const override {
    return "->";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Implication;
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Impl, "Impl"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Impl, implExpr);

}
