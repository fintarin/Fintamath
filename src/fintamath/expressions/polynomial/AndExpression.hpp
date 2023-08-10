#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  explicit AndExpression(const ArgumentsPtrVector &inChildren);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::AndExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr boolSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr notSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr orSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}