#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression>,
                        public std::enable_shared_from_this<IndexExpression> {
public:
  explicit IndexExpression(std::shared_ptr<IMathObject> lhsChild, std::shared_ptr<IMathObject> rhsChild);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> simplify() override;
};

}