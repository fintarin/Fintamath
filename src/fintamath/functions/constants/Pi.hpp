#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {
  class Pi : public IFunctionCRTP<Pi> {
  public:
    Pi() = default;

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
