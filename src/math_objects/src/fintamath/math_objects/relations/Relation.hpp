#pragma once

#include "fintamath/math_objects/MathObject.hpp"

class Relation : public MathObject {
public:
  ~Relation() override = default;
};

using RelationPtr = std::shared_ptr<Relation>;
