#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {
  class Pi : public IConstantCRTP<Pi> {
  public:
    Rational getValue(int64_t precision) const override;

    std::string toString() const override;
  };
}
