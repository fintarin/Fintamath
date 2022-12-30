#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string E::toString() const {
    return "e";
  }

  Expression E::getValue() const {
    return E_NUM;
  }
}
