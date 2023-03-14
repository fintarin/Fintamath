#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression> {
public:
  explicit IndexExpression(const shared_ptr<IMathObject> &lhsChild, const shared_ptr<IMathObject> &rhsChild);
};

}
