#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class UnaryPlus final : public IOperatorCRTP<IArithmetic, UnaryPlus, IArithmetic> {
public:
  UnaryPlus() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "+";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::UnaryPlus;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

}
