#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Div : public IOperatorCRTP<Div, IArithmetic, IArithmetic> {
public:
  Div() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string toString() const override {
    return "/";
  }

protected:
  Expression call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const override;
};

}
