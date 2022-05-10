#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  Rational E::getValue(int64_t precision) const {
    return getE(precision);
  }

  std::string E::toString() const {
    return "e";
  }
}
