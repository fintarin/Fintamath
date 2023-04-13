#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/expressions/binary/CompExpression.hpp"

namespace fintamath {

Expression solve(const Expression &rhs) {
  if (auto compExpr = cast<CompExpression>(rhs.getChildren().front()->clone())) {
    compExpr->markAsSolution();

    ArgumentsPtrVector vars = compExpr->getVariables();

    return *compExpr;
  }

  return rhs;
}

}
