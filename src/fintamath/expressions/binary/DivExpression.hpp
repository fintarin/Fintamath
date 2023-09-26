#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class DivExpression : public IBinaryExpressionCRTP<DivExpression> {
public:
  explicit DivExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::DivExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr numSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr nestedRationalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr gcdSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr nestedNumeratorRationalSimplify(const ArgumentPtrVector &lhsChildren, const ArgumentPtr &rhs);

  static ArgumentPtr trigSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> sumSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> sumMulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> mulSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhs);

  static ArgumentPtr addRatesToValue(const ArgumentPtrVector &rates, const ArgumentPtr &value);

  static Integer getGcd(const ArgumentPtrVector &children);
};

}