#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Nequiv : public IOperatorCRTP<Boolean, Nequiv, Boolean, Boolean> {
  FINTAMATH_CLASS_BODY(Nequiv, IOperator)

public:
  std::string toString() const override {
    return "!<->";
  }

  static constexpr bool isAssociativeStatic() noexcept {
    return true;
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Equivalence;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Nequiv, nequivExpr);

}
