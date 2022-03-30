#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

class Number : public Node {
public:
  ~Number() override = 0;
};

inline Number::~Number() = default;
