#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

MulExpression::MulExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(Mul(), inChildren) {
}

std::string MulExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  if (!prevChild && *inChild == Integer(-1)) {
    return Neg().toString();
  }

  return (prevChild && *prevChild != Integer(-1) ? " " : "") + inChild->toString();
}

ArgumentPtr MulExpression::negate() const {
  MulExpression mulExpr = *this;
  mulExpr.addElement(std::make_shared<Integer>(-1));
  return mulExpr.simplify();
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::simplifyDivisions, //
      &MulExpression::mulRates,          //
      &MulExpression::simplifyNumbers,   //
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForPreSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::simplifyNegations, //
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForPostSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::mulPolynoms, //
  };
  return simplifyFunctions;
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateValuePair(const ArgumentPtr &rhsChild) {
  if (const auto &powExpr = cast<IExpression>(rhsChild); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {std::make_shared<Integer>(1), rhsChild};
}

ArgumentPtr MulExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeFunctionExpression(Add(), rates);
  return makeRawFunctionExpression(Pow(), value, ratesSum);
}

ArgumentPtr MulExpression::simplifyNumbers(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                           const ArgumentPtr &rhsChild) {
  if (*lhsChild == Integer(0)) {
    return lhsChild;
  }

  if (*lhsChild == Integer(1)) {
    return rhsChild;
  }

  return {};
}

ArgumentPtr MulExpression::simplifyDivisions(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {
  const std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  bool isLhsDiv = false;
  bool isRhsDiv = false;

  if (lhsExpr && is<Div>(lhsExpr->getFunction())) {
    isLhsDiv = true;
  }

  if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    isRhsDiv = true;
  }

  ArgumentPtr numerator;
  ArgumentPtr denominator;

  if (isLhsDiv && isRhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), lhsExpr->getChildren().front(), rhsExpr->getChildren().front());
    denominator = makeRawFunctionExpression(Mul(), lhsExpr->getChildren().back(), rhsExpr->getChildren().back());
  }
  else if (isLhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), lhsExpr->getChildren().front(), rhsChild);
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), lhsChild, rhsExpr->getChildren().front());
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  return makeFunctionExpression(Div(), numerator, denominator);
}

ArgumentPtr MulExpression::mulPolynoms(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                       const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhsChild);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhsChild);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(makeRawFunctionExpression(Mul(), lhsSubChild->clone(), rhsSubChild->clone()));
    }
  }

  return makeFunctionExpression(Add(), resultVect);
}

ArgumentPtr MulExpression::mulRates(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                    const ArgumentPtr &rhsChild) {
  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyNegations(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {
  const auto &lhsExpr = cast<IExpression>(lhsChild);
  const auto &rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && is<Neg>(lhsExpr->getFunction()) && is<Neg>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(), lhsExpr->getChildren().front(), rhsExpr->getChildren().front());
  }

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), lhsExpr->getChildren().front(), std::make_shared<Integer>(-1), rhsChild);
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), rhsExpr->getChildren().front(), std::make_shared<Integer>(-1), lhsChild);
  }

  return {};
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

}
