#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression> {
public:
  explicit IndexExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}
