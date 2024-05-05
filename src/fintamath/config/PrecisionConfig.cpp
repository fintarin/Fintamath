#include "fintamath/config/PrecisionConfig.hpp"

#include "fintamath/numbers/Real.hpp"

namespace fintamath::detail {

PrecisionConfig::PrecisionConfig() {
  constexpr unsigned defaultPrecision = 20;
  Real::setPrecisionStatic(defaultPrecision);
}

}
