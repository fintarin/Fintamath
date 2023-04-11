#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Add ADD;

SumExpression::SumExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(ADD, children) {
}

string SumExpression::childToString(const ArgumentPtr &child, bool isFirst) const {
  bool negate = false;
  ArgumentPtr childToStr;
  if (auto negExpr = cast<IExpression>(child); negExpr && is<Neg>(negExpr->getFunction())) {
    childToStr = negExpr->getChildren()[0];
    negate = true;
  }
  else {
    childToStr = child;
  }

  string result;
  if (auto invExpr = cast<IExpression>(childToStr); invExpr && is<Inv>(invExpr->getFunction())) {
    result = "1/" + invExpr->getChildren()[0]->toString();
  }
  else {
    result = childToStr->toString();
  }

  if (!negate && result.front() == '-') {
    negate = true;
    result = result.substr(1, result.size() - 1);
  }

  if (negate) {
    result = (isFirst ? "-" : " - ") + result;
  }
  else {
    result = (isFirst ? "" : " + ") + result;
  }

  return result;
}

ArgumentPtr SumExpression::negate() const {
  SumExpression neg = *this;

  for (auto &child : neg.children) {
    child = makeRawFunctionExpression(Neg(), {child});
  }

  return neg.simplify();
}

SumExpression::FunctionsVector SumExpression::getSimplifyFunctions() const {
  return {&SumExpression::simplifyNumber, &SumExpression::simplifyNegation, &SumExpression::coefficientsProcessing};
}

ArgumentPtr SumExpression::simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsInt = cast<Integer>(lhsChild); lhsInt && *lhsInt == ZERO) {
    return rhsChild;
  }
  if (const auto rhsInt = cast<Integer>(rhsChild); rhsInt && *rhsInt == ZERO) {
    return lhsChild;
  }

  bool lhsNeg = false;
  bool rhsNeg = false;

  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  shared_ptr<const INumber> lhsNum = nullptr;
  shared_ptr<const INumber> rhsNum = nullptr;

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    lhsNum = cast<INumber>(lhsExpr->getChildren().front());
    if (lhsNum) {
      lhsNum = -*lhsNum;
    }
  }
  else {
    lhsNum = cast<INumber>(lhsChild);
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    rhsNum = cast<INumber>(rhsExpr->getChildren().front());
    if (rhsNum) {
      rhsNum = -*rhsNum;
    }
  }
  else {
    rhsNum = cast<INumber>(rhsChild);
  }

  if (lhsNum && rhsNum) {
    return *lhsNum + *rhsNum;
  }

  return {};
}

ArgumentPtr SumExpression::simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Neg>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return make_shared<Integer>(ZERO);
  }
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Neg>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return make_shared<Integer>(ZERO);
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> SumExpression::getRateAndValue(const ArgumentPtr &rhsChild) {
  if (const auto &exprValue = cast<IExpression>(rhsChild); exprValue && is<Mul>(exprValue->getFunction())) {
    ArgumentsPtrVector args = exprValue->getChildren();
    if (const auto &numberValue = cast<INumber>(args.front())) {
      if (args.size() - 1 == 1) {
        return {args.front(), args[1]};
      }
      ArgumentPtr mulExpr = makeFunctionExpression(Mul(), ArgumentsPtrVector{args.begin() + 1, args.end()});
      return {args.front(), mulExpr};
    }
  }
  if (const auto &exprValue = cast<IExpression>(rhsChild); exprValue && is<Neg>(exprValue->getFunction())) {
    ArgumentsPtrVector args = exprValue->getChildren();
    return {NEG_ONE.clone(), args.front()};
  }

  return {ONE.clone(), rhsChild};
}

ArgumentPtr SumExpression::addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value) {
  ArgumentPtr rateSum = makeRawFunctionExpression(Add(), rate);
  return makeFunctionExpression(Mul(), ArgumentsPtrVector{rateSum, value});
}

ArgumentPtr SumExpression::coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::pair<ArgumentPtr, ArgumentPtr> lhsRateValue = getRateAndValue(lhsChild);
  std::pair<ArgumentPtr, ArgumentPtr> rhsRateValue = getRateAndValue(rhsChild);

  ArgumentPtr lhsChildRate = lhsRateValue.first;
  ArgumentPtr rhsChildRate = rhsRateValue.first;

  ArgumentPtr lhsChildValue = lhsRateValue.second;
  ArgumentPtr rhsChildValue = rhsRateValue.second;

  if (lhsChildValue->toString() == rhsChildValue->toString()) {
    return addRateToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

bool SumExpression::comparator(const ArgumentPtr &left, const ArgumentPtr &right) const {
  ArgumentPtr lhs;
  ArgumentPtr rhs;

  if (auto lhsExpr = cast<IExpression>(left); lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    lhs = lhsExpr->getChildren().front();
  }
  else {
    lhs = left;
  }

  if (auto rhsExpr = cast<IExpression>(right); rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    rhs = rhsExpr->getChildren().front();
  }
  else {
    rhs = right;
  }

  return IPolynomExpression::comparator(lhs, rhs);
}

}
