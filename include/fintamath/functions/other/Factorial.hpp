#pragma once

#include <cassert>

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Factorial : public IOperatorCRTP<INumber, Factorial, INumber> {
public:
  Factorial() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return std::string(order, '!');
  }

  uint64_t getOrder() const {
    return order;
  }

  void setOrder(int64_t order) {
    assert(order > 0);
    this->order = order;
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;

private:
  int64_t order = 1;
};

}
