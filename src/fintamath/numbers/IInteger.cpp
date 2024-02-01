#include "fintamath/numbers/IInteger.hpp"

namespace fintamath {

IInteger::IntegerParser &IInteger::getParser() {
  static IntegerParser parser;
  return parser;
}

}
