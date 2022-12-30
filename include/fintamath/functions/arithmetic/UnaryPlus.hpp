#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus : public IOperatorCRTP<UnaryPlus, IArithmetic> {
public:
  UnaryPlus() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "+";
  }

protected:
  Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
};

}
