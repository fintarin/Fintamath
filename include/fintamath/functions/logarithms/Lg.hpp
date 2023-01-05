#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Lg : public IFunctionCRTP<Lg, INumber> {
public:
  Lg() = default;

  std::string toString() const override {
    return "lg";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
