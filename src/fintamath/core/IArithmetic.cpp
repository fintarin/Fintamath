#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

IArithmetic::ArithmeticParser &IArithmetic::getParser() {
  static ArithmeticParser parser;
  return parser;
}

}
