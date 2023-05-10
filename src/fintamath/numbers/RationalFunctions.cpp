#include "fintamath/numbers/RationalFunctions.hpp"

namespace fintamath {

Rational abs(const Rational &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

}
