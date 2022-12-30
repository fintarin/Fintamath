#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Pi::toString() const {
    return "pi";
  }

  Expression Pi::getValue() const {
    return PI_NUM;
  }
}
