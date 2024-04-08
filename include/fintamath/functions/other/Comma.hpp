#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Comma : public IOperatorCRTP<IMathObject, Comma, IMathObject, IMathObject> {
  FINTAMATH_CLASS_BODY(Comma, IOperator)

public:
  std::string toString() const override {
    return ",";
  }

  static constexpr bool isAssociativeStatic() noexcept {
    return true;
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Comma;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Comma, commaExpr);

}
