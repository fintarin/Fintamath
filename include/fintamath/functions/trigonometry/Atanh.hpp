#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Atanh : public IFunctionCRTP<Atanh, INumber> {
public:
  Atanh() = default;

  std::string toString() const override {
    return "atanh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
