#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class LogExpression : public IBinaryExpressionCRTP<LogExpression> {
public:
  explicit LogExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

private:
  static ArgumentPtr numbersSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}