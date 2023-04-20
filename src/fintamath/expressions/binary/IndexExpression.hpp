#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression> {
public:
  explicit IndexExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  ArgumentsPtrVector getVariablesUnsorted() const override;
};

}
