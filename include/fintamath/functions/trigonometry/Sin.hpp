#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Sin : public IFunctionCRTP<Sin, INumber> {
public:
  Sin() = default;

  std::string toString() const override {
    return "sin";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
