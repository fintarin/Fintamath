#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class Acos : public IFunctionCRTP<Acos, INumber> {
  public:
    Acos() = default;

    std::string toString() const {
      return "acos";
    }

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
