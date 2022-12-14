#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string E::toString() const {
    return "e";
  }

  std::string E::getClassName() const {
    return "E";
  }

  Expression E::getValue() const {
    return e();
  }
}
