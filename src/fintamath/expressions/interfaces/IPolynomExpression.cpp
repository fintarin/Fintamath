#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
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

  const size_t childrenSize = children.size();

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

  const size_t childrenSize = children.size();

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
  const std::string result = inChild->toString();
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

  CompareResult compare = comparatorChildren(lhs->getChildren(), rhs->getChildren());

  if (compare.unwrapped != 0) {
    return compare.unwrapped;
  }

  if (compare.unary != 0) {
    return compare.unary;
  }

  if (compare.def != 0) {
    return compare.def;
  }

  if (compare.size != 0) {
    return compare.size;
  }

  if (int res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  if (compare.all != 0) {
    return compare.all;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
}

int IPolynomExpression::comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                                       const ArgumentPtr &rhs) const {

  CompareResult compare = comparatorChildren(lhs->getChildren(), {rhs});

  if (compare.unwrapped != 0) {
    return compare.unwrapped;
  }

  if (compare.unary != 0) {
    return compare.unary;
  }

  if (compare.def != 0) {
    return compare.def;
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

  auto lhsFunc = lhs->getFunction();
  auto rhsFunc = rhs->getFunction();

  ArgumentsPtrVector lhsChildren = lhs->getChildren();
  ArgumentsPtrVector rhsChildren = rhs->getChildren();

  {
    ArgumentPtr lhsToCompare = nullptr;
    ArgumentPtr rhsToCompare = nullptr;

    if (lhsChildren.size() == 1) {
      lhsToCompare = lhsChildren.front();
    }
    if (rhsChildren.size() == 1) {
      rhsToCompare = rhsChildren.front();
    }

    if (lhsToCompare || rhsToCompare) {
      if (!lhsToCompare) {
        lhsToCompare = lhs;
      }
      else if (!rhsToCompare) {
        rhsToCompare = rhs;
      }

      if (int res = comparator(lhsToCompare, rhsToCompare); res != 0) {
        return res;
      }
    }
  }

  CompareResult compare = comparatorChildren(lhs->getChildren(), rhs->getChildren());

  if (compare.allVariables != 0) {
    return compare.allVariables;
  }

  if (int res = comparatorVariables(lhs, rhs, isTermsOrderInversed()); res != 0) {
    return res;
  }

  if (compare.def != 0) {
    return compare.def;
  }

  if (compare.all != 0) {
    return compare.all;
  }

  if (compare.size != 0) {
    return compare.size;
  }

  return comparatorFunctions(lhs->getFunction(), rhs->getFunction());
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

size_t IPolynomExpression::getFirstVarChildPosition(const ArgumentsPtrVector &children) {
  for (size_t position = 0; position < children.size(); position++) {
    auto lhsChildExpr = cast<IExpression>(children[position]);
    if (is<Variable>(children[position]) || (lhsChildExpr && hasVariables(lhsChildExpr))) {
      return position;
    }
  }
  return children.size();
}

bool IPolynomExpression::unwrapUnary(ArgumentPtr &lhs) {
  if (const auto lhsExpr = cast<IExpression>(lhs);
      lhsExpr && lhsExpr->getFunction()->getFunctionType() == IFunction::Type::Unary) {

    lhs = lhsExpr->getChildren().front();
    return true;
  }
  return false;
}

IPolynomExpression::CompareResult IPolynomExpression::comparatorChildren(const ArgumentsPtrVector &lhsChildren,
                                                                         const ArgumentsPtrVector &rhsChildren) const {
  CompareResult result = {};
  if (lhsChildren.size() < rhsChildren.size()) {
    result.allVariables = isTermsOrderInversed() ? -1 : 1;
  }

  if (rhsChildren.size() < lhsChildren.size()) {
    result.allVariables = !isTermsOrderInversed() ? -1 : 1;
  }

  size_t lhsStart = getFirstVarChildPosition(lhsChildren);
  size_t rhsStart = getFirstVarChildPosition(rhsChildren);

  for (size_t i = lhsStart, j = rhsStart; i < lhsChildren.size() && j < rhsChildren.size(); i++, j++) {
    ArgumentPtr compLhs = lhsChildren[i];
    ArgumentPtr compRhs = rhsChildren[j];

    if (result.def == 0) {
      result.def = comparator(compLhs, compRhs);
    }

    bool isLhsUnary = unwrapUnary(compLhs);
    bool isRhsUnary = unwrapUnary(compRhs);

    if (result.unary == 0 && isLhsUnary != isRhsUnary) {
      result.unary = !isLhsUnary ? -1 : 1;
    }

    if (result.unwrapped == 0) {
      result.unwrapped = comparator(compLhs, compRhs);
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.unary = 0;
  }

  for (size_t i = 0; i < std::min(lhsChildren.size(), rhsChildren.size()); i++) {
    if (result.all == 0) {
      result.all = comparator(lhsChildren[i], rhsChildren[i]);
    }
    if (result.allVariables == 0) {
      result.allVariables = comparatorVariables(lhsChildren[i], rhsChildren[i], false);
    }
  }

  if (lhsChildren.size() != rhsChildren.size()) {
    result.size = lhsChildren.size() > rhsChildren.size() ? -1 : 1;
  }

  if (result.unwrapped == 0) {
    if (lhsChildren.size() != rhsChildren.size()) {
      result.def = lhsChildren.size() > rhsChildren.size() ? -1 : 1;
    }
  }

  return result;
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

std::shared_ptr<const Variable> IPolynomExpression::getNextVar(ExprTreePathStack &stack) {
  while (!stack.empty()) {
    ArgumentsPtrVector children = stack.top().first->getChildren();

    size_t &exprIndex = stack.top().second;
    exprIndex++;

    bool hasExprChild = false;

    for (; exprIndex < children.size(); exprIndex++) {
      if (const auto &exprChild = cast<IExpression>(children[exprIndex]); exprChild && hasVariables(exprChild)) {
        stack.emplace(exprChild, -1);
        hasExprChild = true;
        break;
      }

      if (const auto &varChild = cast<Variable>(children[exprIndex])) {
        return varChild;
      }
    }

    if (hasExprChild) {
      continue;
    }

    stack.pop();
  }

  return {};
}

}
