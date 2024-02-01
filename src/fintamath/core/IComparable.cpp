#include "fintamath/core/IComparable.hpp"

namespace fintamath {

IComparable::ComparableParser &IComparable::getParser() {
  static ComparableParser parser;
  return parser;
}

}
