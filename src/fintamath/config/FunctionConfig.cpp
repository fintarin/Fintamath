#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

using namespace fintamath;

namespace {

struct FunctionConfig {
  FunctionConfig() {
    IFunction::registerFunctionExpressionMaker([](const IFunction &function, const ArgumentsRefVector &args) {
      return makeFunctionExpression(function, args);
    });
  }
};

const FunctionConfig config;

}
