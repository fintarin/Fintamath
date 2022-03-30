#pragma once

#include "fintamath/math_objects/MathObject.hpp"

class Node : public MathObject {
public:
  ~Node() override = 0;
};

inline Node::~Node() = default;
