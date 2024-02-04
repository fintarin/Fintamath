#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Index final : public IOperatorCRTP<Variable, Index, Variable, Integer> {
public:
  Index() : IOperatorCRTP(Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "_";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Index;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Index, indexExpr);

}
