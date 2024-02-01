#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

IConstant::ConstantParser &IConstant::getParser() {
  static ConstantParser parser;
  return parser;
}

}
