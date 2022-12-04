#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class More : public IOperatorCRTP<More, IComparable, IComparable> {
  public:
    More();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
