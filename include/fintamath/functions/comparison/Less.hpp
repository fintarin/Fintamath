#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Less : public IOperatorCRTP<Boolean, Less, IComparable, IComparable> {
public:
  Less() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return "<";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
