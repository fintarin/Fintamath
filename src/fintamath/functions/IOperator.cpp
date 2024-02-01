#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

IOperator::OperatorParser &IOperator::getParser() {
  static OperatorParser parser;
  return parser;
}

}
