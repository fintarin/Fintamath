#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Comma final : public IOperatorCRTP<IArithmetic, Comma, IMathObject, IMathObject> {
public:
  Comma() : IOperatorCRTP(Priority::Comma, true) {
  }

  std::string toString() const override {
    return ",";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Comma;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Comma, commaExpr);

}
