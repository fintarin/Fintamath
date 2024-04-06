#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Index : public IOperatorCRTP<Variable, Index, Variable, Integer> {
  FINTAMATH_CLASS_BODY(Index, IOperator)

public:
  std::string toString() const override {
    return "_";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Exponentiation;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Index, indexExpr);

}
