#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

IMathObject::MathObjectParser &IMathObject::getParser() {
  static MathObjectParser parser;
  return parser;
}

}
