#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Ln : public IFunctionCRTP<Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
