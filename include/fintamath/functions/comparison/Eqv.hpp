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

class Eqv final : public IOperatorCRTP<Boolean, Eqv, IComparable, IComparable> {
public:
  Eqv() : IOperatorCRTP(Priority::Comparison, true) {
  }

  std::string toString() const override {
    return "=";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Eqv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Eqv, eqvExpr);

}
