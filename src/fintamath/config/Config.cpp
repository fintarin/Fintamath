#include "fintamath/config/Config.hpp"

#include "fintamath/config/PrecisionConfig.hpp"
#include "fintamath/config/TypeConfig.hpp"

namespace fintamath::detail {

Config::Config() {
  static const TypeConfig typeConfig;
  static const PrecisionConfig precisionConfig;
  // static const ExpressionConfig expressionConfig;
}

}
