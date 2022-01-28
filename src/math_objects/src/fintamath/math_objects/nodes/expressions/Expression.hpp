#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "fintamath/math_objects/nodes/Node.hpp"

class Expression : public Node {
public:
  ~Expression() override = 0;
};

inline Expression::~Expression() = default;

#endif // EXPRESSION_HPP
