#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class DivExpression : public IBinaryExpressionCRTP<DivExpression> {
public:
  explicit DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

protected:
  ArgumentPtr postSimplify() const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

private:
  static ArgumentPtr numbersSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divPowerSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhs);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);

private:
  static const SimplifyFunctionsVector simplifyFunctions;
};

}