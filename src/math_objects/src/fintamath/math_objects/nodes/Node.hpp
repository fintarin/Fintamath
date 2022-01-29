#pragma once

#include "fintamath/math_objects/MathObject.hpp"

class Node : public MathObject {
public:
  ~Node() override = default;
};

using NodePtr = std::shared_ptr<Node>;
