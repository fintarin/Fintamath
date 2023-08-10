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
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr rationalSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr divSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr polynomSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhsChild);
};

}