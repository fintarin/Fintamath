#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class PowOper final : public IOperatorCRTP<INumber, PowOper, INumber, INumber> {
  FINTAMATH_CLASS_BODY(PowOper)

public:
  std::string toString() const override {
    return "^";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Exponentiation;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}