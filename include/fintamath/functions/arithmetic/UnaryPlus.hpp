#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus final : public IOperatorCRTP<IArithmetic, UnaryPlus, IArithmetic> {
  FINTAMATH_CLASS_BODY(UnaryPlus)

public:
  std::string toString() const noexcept override {
    return "+";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
