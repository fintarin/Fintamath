#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Index : public IOperatorCRTP<IMathObject, Index, IMathObject, IMathObject> {
public:
  Index() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "_";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
