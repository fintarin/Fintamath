#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Min : public IFunctionCRTP<IComparable, Min, IComparable> {
public:
  Min() : IFunctionCRTP(true) {
  }

  std::string toString() const override {
    return "min";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
