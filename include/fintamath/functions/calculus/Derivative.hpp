#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Derivative : public IFunctionCRTP<IComparable, Derivative, IComparable, IComparable> {
public:
  Derivative() : IFunctionCRTP(false) {
  }

  std::string toString() const override {
    return "derivative";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
