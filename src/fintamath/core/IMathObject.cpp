#include "fintamath/core/IMathObject.hpp"

#include <ostream>

namespace fintamath {

IMathObject::MathObjectParser &IMathObject::getParser() {
  static MathObjectParser parser;
  return parser;
}

}
