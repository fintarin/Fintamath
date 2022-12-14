#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Pi::toString() const {
    return "pi";
  }

  std::string Pi::getClassName() const {
    return "Pi";
  }

  Expression Pi::getValue() const {
    return pi();
  }
}
