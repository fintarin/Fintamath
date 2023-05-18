#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Mul : public IOperatorCRTP<IArithmetic, Mul, IArithmetic, IArithmetic> {
public:
  Mul() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string toString() const override {
    return "*";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Mul);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
