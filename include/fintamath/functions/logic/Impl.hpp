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

class Impl final : public IOperatorCRTP<Boolean, Impl, Boolean, Boolean> {
public:
  Impl() : IOperatorCRTP(Priority::Implication, false) {
  }

  std::string toString() const override {
    return "->";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Impl;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Impl, implExpr);

}
