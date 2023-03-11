#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Not : public IOperatorCRTP<Boolean, Not, Boolean> {
public:
  Not() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "~";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
