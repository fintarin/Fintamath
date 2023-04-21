#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

map<string, shared_ptr<IFunction>, std::less<>> CompExpression::oppositeFunctionsMap;

}

using namespace fintamath;

namespace {

struct CompExpressionConfig {
  CompExpressionConfig() {
    CompExpression::addOppositeFunctions(make_shared<Eqv>(), make_shared<Eqv>());
    CompExpression::addOppositeFunctions(make_shared<Neqv>(), make_shared<Neqv>());
    CompExpression::addOppositeFunctions(make_shared<More>(), make_shared<Less>());
    CompExpression::addOppositeFunctions(make_shared<Less>(), make_shared<More>());
    CompExpression::addOppositeFunctions(make_shared<MoreEqv>(), make_shared<LessEqv>());
    CompExpression::addOppositeFunctions(make_shared<LessEqv>(), make_shared<MoreEqv>());
  }
};

const CompExpressionConfig config;

}
