#include "fintamath/config/Config.hpp"

#include "fintamath/config/ConverterConfig.hpp"
#include "fintamath/config/ExpressionConfig.hpp"
#include "fintamath/config/PrecisionConfig.hpp"
#include "fintamath/config/TypeConfig.hpp"

namespace fintamath::detail {

Config::Config() {
  [[maybe_unused]] static const TypeConfig typeConfig;
  [[maybe_unused]] static const PrecisionConfig precisionConfig;
  [[maybe_unused]] static const ConverterConfig converterConfig;
  [[maybe_unused]] static const ExpressionConfig expressionConfig;
}

}
