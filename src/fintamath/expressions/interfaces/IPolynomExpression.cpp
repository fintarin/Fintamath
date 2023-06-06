#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

std::shared_ptr<IFunction> IPolynomExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IPolynomExpression::getChildren() const {
  return children;
}

std::string IPolynomExpression::toString() const {
  if (!is<IOperator>(func)) {
    return functionToString(*func, children);
  }

  std::string result;

  result += operatorChildToString(children.front(), {});

  for (size_t i = 1; i < children.size(); i++) {
    result += operatorChildToString(children[i], children[i - 1]);
  }

  return result;
}

ArgumentPtr IPolynomExpression::simplify() const {
  ArgumentPtr simpl = cast<IPolynomExpression>(clone());

  preSimplifyChild(simpl);
  postSimplifyChild(simpl);

  return simpl;
}

ArgumentPtr IPolynomExpression::useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs, size_t lhsChildPos,
                                                     size_t rhsChildPos) const {
  const auto &lhs = children[lhsChildPos];
  const auto &rhs = children[rhsChildPos];

  for (const auto &simplFunc : simplFuncs) {
    if (auto res = simplFunc(*func, lhs, rhs)) {
      return res;
    }
  }

  return {};
}

ArgumentPtr IPolynomExpression::preSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  {
    ArgumentsPtrVector oldChildren = simpl->children;
    simpl->children.clear();

    for (auto &child : oldChildren) {
      preSimplifyChild(child);
      simpl->addElement(child);
    }
  }

  simpl->preSimplifyRec();

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

void IPolynomExpression::preSimplifyRec() {
  sort();

  size_t childrenSize = children.size();

  for (size_t i = 1; i < children.size(); i++) {
    ArgumentPtr res = callFunction(*func, {children[i - 1], children[i]});

    if (!res) {
      res = useSimplifyFunctions(getFunctionsForPreSimplify(), i - 1, i);
    }

    if (!res) {
      res = useSimplifyFunctions(getFunctionsForSimplify(), i - 1, i);
    }

    if (res) {
      children[i - 1] = res;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
  }

  if (children.size() != childrenSize) {
    preSimplifyRec();
  }
}

ArgumentPtr IPolynomExpression::postSimplify() const {
  auto simpl = cast<IPolynomExpression>(clone());

  {
    ArgumentsPtrVector oldChildren = simpl->children;
    simpl->children.clear();

    for (auto &child : oldChildren) {
      postSimplifyChild(child);
      simpl->addElement(child);
    }
  }

  simpl->postSimplifyRec();

  if (simpl->children.size() == 1) {
    return simpl->children.front();
  }

  return simpl;
}

void IPolynomExpression::postSimplifyRec() {
  sort();

  size_t childrenSize = children.size();

  for (size_t i = 1; i < children.size(); i++) {
    ArgumentPtr res = callFunction(*func, {children[i - 1], children[i]});

    if (!res) {
      res = useSimplifyFunctions(getFunctionsForPostSimplify(), i - 1, i);
    }

    if (!res) {
      res = useSimplifyFunctions(getFunctionsForSimplify(), i - 1, i);
    }

    if (res) {
      children[i - 1] = res;
      children.erase(children.begin() + ArgumentsPtrVector::iterator::difference_type(i));
      i--;
    }
  }

  if (children.size() != childrenSize) {
    postSimplifyRec();
  }
}

IPolynomExpression::SimplifyFunctionsVector IPolynomExpression::getFunctionsForSimplify() const {
  return {};
}

IPolynomExpression::SimplifyFunctionsVector IPolynomExpression::getFunctionsForPreSimplify() const {
  return {};
}

IPolynomExpression::SimplifyFunctionsVector IPolynomExpression::getFunctionsForPostSimplify() const {
  return {};
}

std::string IPolynomExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = inChild->toString();
  return prevChild ? (putInSpaces(func->toString()) + result) : result;
}

bool IPolynomExpression::isTermsOrderInversed() const {
  return false;
}

bool IPolynomExpression::isComparableOrderInversed() const {
  return false;
}

void IPolynomExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.empty()) {
    throw InvalidInputFunctionException(toString(), {});
  }

  children = childVect;
}

void IPolynomExpression::sort() {
  std::sort(children.begin(), children.end(), [this](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return comparator(lhs, rhs) < 0;
  });
}

int IPolynomExpression::comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr && !rhsExpr) {
    return comparatorNonExpressions(lhs, rhs);
  }

  auto lhsPolynom = cast<IPolynomExpression>(lhsExpr);
  auto rhsPolynom = cast<IPolynomExpression>(rhsExpr);

  if (lhsPolynom && rhsPolynom) {
    return comparatorPolynoms(lhsPolynom, rhsPolynom);
  }

  if (lhsPolynom && !rhsPolynom) {
    return comparatorPolynomAndNonPolynom(lhsPolynom, rhs);
  }

  if (!lhsPolynom && rhsPolynom) {
    return comparatorPolynomAndNonPolynom(rhsPolynom, lhs) * -1;
  }

  if (lhsExpr && !rhsExpr) {
    return comparatorExpressionAndNonExpression(lhsExpr, rhs);
  }

  if (!lhsExpr && rhsExpr) {
    return comparatorExpressionAndNonExpression(rhsExpr, lhs) * -1;
  }

  return comparatorExpressions(lhsExpr, rhsExpr);
}

int IPolynomExpression::comparatorNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  if (is<ILiteral>(lhs) && !is<ILiteral>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<ILiteral>(lhs) && is<ILiteral>(rhs)) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (is<Variable>(lhs) && !is<Variable>(rhs)) {
    return !isTermsOrderInversed() ? -1 : 1;
  }
  if (!is<Variable>(lhs) && is<Variable>(rhs)) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (*lhs == *rhs) {
    return 0;
  }

  if (auto lhsComp = cast<IComparable>(lhs)) {
    if (auto rhsComp = cast<IComparable>(rhs)) {
      if (isComparableOrderInversed()) {
        return *lhsComp < *rhsComp ? -1 : 1;
      }

      return *lhsComp > *rhsComp ? -1 : 1;
    }
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

int IPolynomExpression::comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                                           const std::shared_ptr<const IPolynomExpression> &rhs) const {

  if (int res = comparatorChildren(lhs->getChildren(), rhs->getChildren(), true); res != 0) {
    return res;
  }

  if (int res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  if (int res = comparatorChildren(lhs->getChildren(), rhs->getChildren(), true, false); res != 0) {
    return res;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
}

int IPolynomExpression::comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                                       const ArgumentPtr &rhs) const {

  if (int res = comparatorChildren(lhs->getChildren(), {rhs}, true); res != 0) {
    return res;
  }

  if (int res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  return -1;
}

int IPolynomExpression::comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                                             const ArgumentPtr &rhs) const {

  if (auto oper = cast<IOperator>(lhs->getFunction());
      oper && oper->getOperatorPriority() <= IOperator::Priority::PrefixUnary) {

    if (int res = comparator(lhs->getChildren().front(), rhs); res != 0) {
      return res;
    }

    return 1;
  }

  if (auto res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  return !isTermsOrderInversed() ? -1 : 1;
}

int IPolynomExpression::comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                                              const std::shared_ptr<const IExpression> &rhs) const {

  if (int res = comparatorFunctionChildren(lhs->getChildren(), rhs->getChildren()); res != 0) {
    return res;
  }

  if (int res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  if (int res = comparatorChildren(lhs->getChildren(), rhs->getChildren(), false, false); res != 0) {
    return res;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
}

std::shared_ptr<const Variable> IPolynomExpression::getNextVar(ExprTreePathStack &stack) const {
  while (!stack.empty()) {
    ArgumentsPtrVector childVect = stack.top().first->getChildren();
    size_t &idx = stack.top().second;
    bool isStackPushed = false;

    idx++;
    for (; idx < childVect.size(); idx++) {
      if (const auto &exprChild = cast<IExpression>(childVect[idx]); exprChild && hasVariables(exprChild)) {
        stack.emplace(exprChild, -1);
        isStackPushed = true;
        break;
      }
      if (const auto &varChild = cast<Variable>(childVect[idx])) {
        return varChild;
      }
    }
    if (isStackPushed) {
      continue;
    }
    stack.pop();
  }

  return {};
}

int IPolynomExpression::comparatorVariables(const ArgumentPtr &lhs, const ArgumentPtr &rhs,
                                            bool isTermsOrderInversed) const {
  ExprTreePathStack lhsPath;
  ExprTreePathStack rhsPath;

  std::shared_ptr<const Variable> lhsVar;
  std::shared_ptr<const Variable> rhsVar;

  if (const auto &expr = cast<IExpression>(lhs)) {
    lhsPath.emplace(expr, -1);
    lhsVar = getNextVar(lhsPath);
  }
  else if (const auto &var = cast<Variable>(lhs)) {
    lhsVar = var;
  }

  if (const auto &expr = cast<IExpression>(rhs)) {
    rhsPath.emplace(expr, -1);
    rhsVar = getNextVar(rhsPath);
  }
  else if (const auto &var = cast<Variable>(rhs)) {
    rhsVar = var;
  }

  if (lhsVar && !rhsVar) {
    return !isTermsOrderInversed ? -1 : 1;
  }

  if (!lhsVar && rhsVar) {
    return isTermsOrderInversed ? -1 : 1;
  }

  while (lhsVar && rhsVar) {
    if (int res = comparatorNonExpressions(lhsVar, rhsVar); res != 0) {
      return res;
    }
    lhsVar = getNextVar(lhsPath);
    rhsVar = getNextVar(rhsPath);
  }

  return 0;
}

int IPolynomExpression::comparatorFunctionChildren(const ArgumentsPtrVector &lhsChildren,
                                                   const ArgumentsPtrVector &rhsChildren) const {
  if (lhsChildren.size() < rhsChildren.size()) {
    return isTermsOrderInversed() ? -1 : 1;
  }

  if (rhsChildren.size() < lhsChildren.size()) {
    return !isTermsOrderInversed() ? -1 : 1;
  }

  for (size_t i = 0; i < lhsChildren.size(); i++) {
    if (int res = comparatorVariables(lhsChildren[i], rhsChildren[i], false); res != 0) {
      return res;
    }
  }

  return 0;
}

int IPolynomExpression::comparatorChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren,
                                           bool ignoreUnaryIfPossible, bool ignoreChildWithoutVars) const {

  size_t lhsStart = 0;
  for (; lhsStart < lhsChildren.size(); lhsStart++) {
    auto lhsChildExpr = cast<IExpression>(lhsChildren[lhsStart]);
    if (is<Variable>(lhsChildren[lhsStart]) || (lhsChildExpr && hasVariables(lhsChildExpr))) {
      break;
    }
  }

  size_t rhsStart = 0;
  for (; rhsStart < rhsChildren.size(); rhsStart++) {
    auto rhsChildExpr = cast<IExpression>(rhsChildren[rhsStart]);
    if (is<Variable>(rhsChildren[rhsStart]) || (rhsChildExpr && hasVariables(rhsChildExpr))) {
      break;
    }
  }

  int comparatorUnary = 0;

  for (size_t i = lhsStart, j = rhsStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    if (ignoreUnaryIfPossible) {
      bool isLhsUnary = false;

      if (const auto lhsExpr = cast<IExpression>(compLhs);
          lhsExpr && lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

        compLhs = lhsExpr->getChildren().front();
        isLhsUnary = true;
      }

      bool isRhsUnary = false;

      if (const auto rhsExpr = cast<IExpression>(compRhs);
          rhsExpr && rhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

        compRhs = rhsExpr->getChildren().front();
        isRhsUnary = true;
      }

      if (comparatorUnary == 0 && isLhsUnary != isRhsUnary) {
        comparatorUnary = !isLhsUnary ? -1 : 1;
      }
    }

    if (int res = comparator(compLhs, compRhs); res != 0) {
      return res;
    }
  }

  if (comparatorUnary != 0 && lhsChildren.size() == rhsChildren.size()) {
    return comparatorUnary;
  }

  if (!ignoreChildWithoutVars) {
    for (size_t i = 0; i < std::min(lhsChildren.size(), rhsChildren.size()); i++) {
      if (int res = comparator(lhsChildren[i], rhsChildren[i]); res != 0) {
        return res;
      }
    }
  }

  if (lhsChildren.size() == rhsChildren.size()) {
    return 0;
  }

  return lhsChildren.size() > rhsChildren.size() ? -1 : 1;
}

int IPolynomExpression::comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                                            const std::shared_ptr<const IFunction> &rhs) {

  if (is<IOperator>(lhs) && !is<IOperator>(rhs)) {
    return -1;
  }
  if (!is<IOperator>(lhs) && is<IOperator>(rhs)) {
    return 1;
  }

  if (*lhs == *rhs) {
    return 0;
  }

  return lhs->toString() < rhs->toString() ? -1 : 1;
}

// ArgumentPtr IPolynomExpression::findFirstPolynomChild(const ArgumentPtr &rhs) {
//   auto res = cast<IExpression>(rhs);

//   while (res && !is<IPolynomExpression>(res)) {
//     res = cast<IExpression>(res->getChildren().front());
//   }

//   if (is<IPolynomExpression>(res)) {
//     return res;
//   }

//   return {};
// }

}
