#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Rad : public IFunctionCRTP<INumber, Rad, INumber> {
public:
  Rad() = default;

  std::string toString() const override {
    return "rad";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
