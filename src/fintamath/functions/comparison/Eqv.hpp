#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class Eqv : public IOperatorCRTP<Eqv, IMathObject, IMathObject> {
  public:
    Eqv();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
