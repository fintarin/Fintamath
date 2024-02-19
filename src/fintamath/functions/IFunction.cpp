#include "fintamath/functions/IFunction.hpp"

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

const IFunction::FunctionNameToOrderMap &IFunction::getFunctionNameToOrderMap() {
  return getFunctionNameToOrderMutableMap();
}

IFunction::FunctionNameToOrderMap &IFunction::getFunctionNameToOrderMutableMap() {
  static FunctionNameToOrderMap map;
  return map;
}

IFunction::FunctionParser &IFunction::getParser() {
  static FunctionParser parser;
  return parser;
}

}
