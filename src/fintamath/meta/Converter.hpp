#pragma once

#include "fintamath/meta/MultiMethod.hpp"
#include <memory>

namespace fintamath {
  class MathObject;
}

namespace fintamath::meta {
  MultiMethod<std::unique_ptr<MathObject>(const MathObject &, const MathObject &)> initConverter();

  const auto convert = initConverter();
}