#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {
  class Pi : public IConstantCRTP<Pi> {
  public:
    Rational getValue(int64_t precision) const override; // TODO change to operator Rational()

    std::string toString() const override;

    std::string getClassName() const override;
  };
}
