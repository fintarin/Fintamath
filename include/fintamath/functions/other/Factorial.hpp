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

  size_t getOrder() const {
    return order;
  }

  void setOrder(size_t inOrder) {
    assert(inOrder > 0);
    order = inOrder;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  size_t order = 1;
};

}
