#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression> {
public:
  explicit MulExpression(const ArgumentsPtrVector &inChildren);

  std::string toString() const override;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::MulExpression);
  }

protected:
  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  bool isTermsOrderInversed() const override;

private:
  static ArgumentPtr simplifyConst(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyRationals(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyCallFunction(const IFunction &func, const ArgumentPtr &lhsChild,
                                          const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegations(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulPolynoms(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyPowers(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhsChild);
};

}