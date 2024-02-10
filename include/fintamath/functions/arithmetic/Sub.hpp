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

class Sub final : public IOperatorCRTP<IArithmetic, Sub, IArithmetic, IArithmetic> {
public:
  Sub() : IOperatorCRTP(Priority::Addition) {
  }

  std::string toString() const override {
    return "-";
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::Sub;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Sub, subExpr);

}
