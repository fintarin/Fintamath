#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {
  class E : public IFunctionCRTP<E> {
  public:
    E() = default;

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
