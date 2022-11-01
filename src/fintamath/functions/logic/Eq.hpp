#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {
  class Eq : public IOperatorCRTP<Eq, IMathObject, IMathObject> {
  public:
    Eq();

    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
  };
}
