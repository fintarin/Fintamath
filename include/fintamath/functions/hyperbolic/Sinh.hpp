#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Sinh : public IFunctionCRTP<INumber, Sinh, INumber> {
public:
  Sinh() = default;

  std::string toString() const override {
    return "sinh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
