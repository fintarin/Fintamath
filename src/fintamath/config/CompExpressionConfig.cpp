#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

std::map<std::string, std::shared_ptr<IFunction>, std::less<>> CompExpression::oppositeFunctionsMap;

}

using namespace fintamath;

namespace {

struct CompExpressionConfig {
  CompExpressionConfig() {
    CompExpression::addOppositeFunctions(std::make_shared<Eqv>(), std::make_shared<Eqv>());
    CompExpression::addOppositeFunctions(std::make_shared<Neqv>(), std::make_shared<Neqv>());
    CompExpression::addOppositeFunctions(std::make_shared<More>(), std::make_shared<Less>());
    CompExpression::addOppositeFunctions(std::make_shared<Less>(), std::make_shared<More>());
    CompExpression::addOppositeFunctions(std::make_shared<MoreEqv>(), std::make_shared<LessEqv>());
    CompExpression::addOppositeFunctions(std::make_shared<LessEqv>(), std::make_shared<MoreEqv>());
  }
};

const CompExpressionConfig config;

}
