#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Cot : public IFunctionCRTP<Cot, INumber> {
public:
  Cot() = default;

  std::string toString() const override {
    return "cot";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
