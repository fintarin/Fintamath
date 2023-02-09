#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Asin : public IFunctionCRTP<INumber, Asin, INumber> {
public:
  Asin() = default;

  std::string toString() const override {
    return "asin";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
