#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

MathObjectPtr Pi::call() const {
  return std::make_unique<Real>(PI_NUM);
}

}
