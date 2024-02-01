#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

ILiteral::LiteralParser &ILiteral::getParser() {
  static LiteralParser parser;
  return parser;
}

}
