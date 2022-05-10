#pragma once

#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {
  class Pi : public ConstantImpl<Pi> {
  public:
    Rational getValue(int64_t precision) const override;

    std::string toString() const override;
  };
}
