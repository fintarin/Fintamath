#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Rad : public IFunctionCRTP<INumber, Rad, INumber> {
public:
  Rad() = default;

  std::string toString() const override {
    return "rad";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
