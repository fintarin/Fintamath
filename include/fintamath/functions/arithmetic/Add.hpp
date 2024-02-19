#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add final : public IOperatorCRTP<IArithmetic, Add, IArithmetic, IArithmetic> {
public:
  std::string toString() const override {
    return "+";
  }

  static constexpr bool isAssociativeStatic() {
    return true;
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Addition;
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Add, "Add"};
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Add, addExpr);

}
