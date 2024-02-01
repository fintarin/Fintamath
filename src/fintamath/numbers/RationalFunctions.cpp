#include "fintamath/numbers/RationalFunctions.hpp"

#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

Integer floor(const Rational &rhs) {
  Integer div = rhs.numerator() / rhs.denominator();

  if (rhs.numerator() < 0 && abs(rhs.numerator()) % rhs.denominator() != 0) {
    --div;
  }

  return div;
}

Integer ceil(const Rational &rhs) {
  Integer div = rhs.numerator() / rhs.denominator();

  if (rhs.numerator() >= 0 && abs(rhs.numerator()) % rhs.denominator() != 0) {
    ++div;
  }

  return div;
}

Rational abs(const Rational &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

}
