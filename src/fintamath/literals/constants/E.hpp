#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {
  class E : public IConstantCRTP<E> {
  public:
    Rational getValue(int64_t precision) const override;

    std::string toString() const override;
  };
}
