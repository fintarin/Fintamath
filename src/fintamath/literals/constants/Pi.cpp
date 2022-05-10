#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  Rational Pi::getValue(int64_t precision) const {
    return getPi(precision);
  }

  std::string Pi::toString() const {
    return "pi";
  }
}
