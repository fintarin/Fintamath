#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

const IFunction::FunctionOrderMap &IFunction::getFunctionOrderMap() {
  return getFunctionOrderMutableMap();
}

IFunction::FunctionOrderMap &IFunction::getFunctionOrderMutableMap() {
  static FunctionOrderMap orderMap;
  return orderMap;
}

IFunction::FunctionParser &IFunction::getParser() {
  static FunctionParser parser;
  return parser;
}

}
