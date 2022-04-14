#pragma once

#include <memory>

namespace fintamath {
  class MathObject;
  using MathObjectPtr = std::unique_ptr<MathObject>;
}

namespace fintamath::meta {
  MathObjectPtr convertRhsToLhsType(const MathObject &lhs, const MathObject &rhs);
}
