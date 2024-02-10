#include "fintamath/config/Config.hpp"

#include "fintamath/config/ConverterConfig.hpp"
#include "fintamath/config/ExpressionConfig.hpp"
#include "fintamath/config/ParserConfig.hpp"
#include "fintamath/config/PrecisionConfig.hpp"

namespace fintamath {

Config::Config() {
  [[maybe_unused]] static const PrecisionConfig precisionConfig;
  [[maybe_unused]] static const ParserConfig parserConfig;
  [[maybe_unused]] static const ConverterConfig converterConfig;
  [[maybe_unused]] static const ExpressionConfig expressionConfig;
}

}
