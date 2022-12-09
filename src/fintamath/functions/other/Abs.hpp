#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  class Abs : public IFunctionCRTP<Abs, INumber> {
  public:
    Abs() = default;

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
