#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class Lb : public IFunctionCRTP<Lb, INumber> {
  public:
    Lb() = default;

    std::string toString() const {
      return "lb";
    }

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
