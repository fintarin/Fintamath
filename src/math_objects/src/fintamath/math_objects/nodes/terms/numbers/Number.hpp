#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "fintamath/math_objects/nodes/terms/Term.hpp"

class Number : public Term {
public:
  ~Number() override = 0;
};

inline Number::~Number() = default;

#endif // NUMBER_HPP
