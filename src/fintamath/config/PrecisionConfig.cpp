#include "fintamath/config/PrecisionConfig.hpp"

#include "fintamath/numbers/Real.hpp"

namespace fintamath {

PrecisionConfig::PrecisionConfig() {
  constexpr unsigned defaultPrecision = 20;
  Real::setPrecision(defaultPrecision);
}

}
