#pragma once

#include "fintamath/meta/MultiMethod.hpp"

#include <memory>

namespace fintamath {
  class MathObject;
  using MathObjectPtr = std::unique_ptr<MathObject>;
}

namespace fintamath::meta {
  class Converter {
  public:
    static MathObjectPtr convertToBase(const MathObject &, const MathObject &);

  private:
    static const MultiMethod<MathObjectPtr(const MathObject &, const MathObject &)> converter;
  };
}
