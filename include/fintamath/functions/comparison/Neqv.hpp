#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Neqv final : public IOperatorCRTP<Boolean, Neqv, IComparable, IComparable> {
public:
  Neqv() : IOperatorCRTP(Priority::Comparison, true) {
  }

  std::string toString() const override {
    return "!=";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Neqv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Neqv, neqvExpr);

}
