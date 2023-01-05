#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Lb : public IFunctionCRTP<Lb, INumber> {
public:
  Lb() = default;

  std::string toString() const override {
    return "lb";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
