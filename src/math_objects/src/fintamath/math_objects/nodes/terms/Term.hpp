#ifndef TERM_HPP
#define TERM_HPP

#include "fintamath/math_objects/nodes/Node.hpp"

class Term : public Node {
public:
  ~Term() override = 0;
};

inline Term::~Term() = default;

#endif // TERM_HPP
