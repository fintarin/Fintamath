#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Degrees : public IFunctionCRTP<INumber, Degrees, INumber> {
public:
  Degrees() = default;

  std::string toString() const override {
    return "degrees";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
