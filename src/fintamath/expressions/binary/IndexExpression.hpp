#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression> {
public:
  explicit IndexExpression(std::unique_ptr<IMathObject> &&lhs, std::unique_ptr<IMathObject> &&rhs);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};

}