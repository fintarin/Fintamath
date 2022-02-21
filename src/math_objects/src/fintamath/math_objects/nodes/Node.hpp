#pragma once

#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  class Node : public MathObject {
  public:
    ~Node() override = default;
  };

  using NodePtr = std::shared_ptr<Node>;
}
