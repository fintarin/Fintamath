#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "fintamath/math_objects/nodes/terms/Term.hpp"

class Constant : public Term {
public:
  ~Constant() override = default;
};

#endif // CONSTANT_HPP
