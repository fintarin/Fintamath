#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "fintamath/math_objects/nodes/Node.hpp"

class Number : public Node {
public:
  ~Number() override = 0;
};

inline Number::~Number() = default;

#endif // NUMBER_HPP
