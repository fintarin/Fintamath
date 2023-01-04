#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class IExpression;

class Derivative : public IOperatorCRTP<Derivative, IMathObject> {
public:
  Derivative() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "'";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
