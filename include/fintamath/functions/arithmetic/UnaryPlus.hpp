#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus : public IOperatorCRTP<IArithmetic, UnaryPlus, IArithmetic> {
  FINTAMATH_CLASS_BODY(UnaryPlus, IOperator)

public:
  std::string toString() const override {
    return "+";
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::PrefixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
