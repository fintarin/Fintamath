#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "fintamath/math_objects/relations/Relation.hpp"

class Function : public Relation {
public:
  ~Function() override = 0;
};

inline Function::~Function() = default;

#endif // FUNCTION_HPP
