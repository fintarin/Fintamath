#include "fintamath/numbers/RationalFunctions.hpp"

namespace fintamath {

Rational abs(const Rational &rhs) {
  if (rhs < 0) {
    return -rhs;
  }

  return rhs;
}

}
