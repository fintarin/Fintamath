#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class Less : public IOperatorCRTP<Less, IComparable, IComparable> {
  public:
    Less();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
