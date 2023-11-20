#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  explicit AndExpression(ArgumentPtrVector inChildren);

  static MathObjectType getTypeStatic() {
    return MathObjectType::AndExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr boolSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr notSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr orSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}