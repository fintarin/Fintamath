#pragma once

#include "fintamath/meta/MultiMethod.hpp"

#include <memory>

namespace fintamath {
  class MathObject;
  using MathObjectPtr = std::unique_ptr<MathObject>;
}

namespace fintamath::meta {
  MultiMethod<MathObjectPtr(const MathObject &, const MathObject &)> initConverter();

  const auto convert = initConverter();
}