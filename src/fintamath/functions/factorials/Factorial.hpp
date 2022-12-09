#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  class Factorial : public IOperatorCRTP<Factorial, INumber> {
  public:
    Factorial();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
