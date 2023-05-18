#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class LogExpression : public IBinaryExpressionCRTP<LogExpression> {
public:
  explicit LogExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

  // TODO!!! reimplement
  // ArgumentPtr negate() const override;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::LogExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr numSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}