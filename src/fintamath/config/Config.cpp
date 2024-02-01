#include "fintamath/config/Config.hpp"

#include "fintamath/config/ConverterConfig.hpp"
#include "fintamath/config/ExpressionConfig.hpp"
#include "fintamath/config/ParserConfig.hpp"
#include "fintamath/config/PrecisionConfig.hpp"

namespace fintamath {

Config::Config() {
  [[maybe_unused]] const PrecisionConfig precisionConfig;
  [[maybe_unused]] const ParserConfig parserConfig;
  [[maybe_unused]] const ConverterConfig converterConfig;
  [[maybe_unused]] const ExpressionConfig expressionConfig;
}

}
