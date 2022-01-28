#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "fintamath/math_objects/relations/Relation.hpp"

class Operator : public Relation {
public:
  ~Operator() override = 0;
};

inline Operator::~Operator() = default;

#endif // OPERATOR_HPP
