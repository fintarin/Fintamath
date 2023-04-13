#include "fintamath/expressions/binary/IndexExpression.hpp"

#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

const Index INDEX;

IndexExpression::IndexExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)
    : IBinaryExpressionCRTP(INDEX, lhsChild, rhsChild) {
}

ArgumentsPtrVector IndexExpression::getVariables() const {
  return {clone()};
}

}
