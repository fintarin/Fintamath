#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Sqrt : public IFunctionCRTP<Sqrt, INumber> {
public:
  Sqrt() = default;

  std::string toString() const override {
    return "sqrt";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
