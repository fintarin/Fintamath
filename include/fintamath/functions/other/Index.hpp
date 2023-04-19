#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Index : public IOperatorCRTP<Variable, Index, Variable, IComparable> {
public:
  Index() : IOperatorCRTP(IOperator::Priority::Exponentiation, false, false) {
  }

  string toString() const override {
    return "_";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
