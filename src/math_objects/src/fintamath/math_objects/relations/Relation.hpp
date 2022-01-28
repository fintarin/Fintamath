#ifndef RELATION_HPP
#define RELATION_HPP

#include "fintamath/math_objects/MathObject.hpp"

class Relation : public MathObject {
public:
  ~Relation() override = 0;
};

inline Relation::~Relation() = default;

#endif // RELATION_HPP
