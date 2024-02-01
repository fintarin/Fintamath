#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

INumber::NumberParser &INumber::getParser() {
  static NumberParser parser;
  return parser;
}

}
