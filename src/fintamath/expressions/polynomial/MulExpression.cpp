#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <memory>
#include <set>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

const Mul MUL;

struct MulExpression::ObjectPow {
  std::shared_ptr<IMathObject> obj;
  SumExpression pow = SumExpression({});

  ObjectPow(std::shared_ptr<IMathObject> obj) : obj(std::move(obj)) {
  }

  std::shared_ptr<IMathObject> getPowIfInteger() const {
    ArgumentsPtrVector polynom = pow.getPolynom();

    if (polynom.size() != 1) {
      return {};
    }

    std::shared_ptr<IMathObject> powValue = polynom.front()->toMinimalObject();

    if (is<Integer>(powValue)) {
      return powValue;
    }

    return {};
  }

  std::shared_ptr<IMathObject> getPowIfSingle() const {
    ArgumentsPtrVector polynom = pow.getPolynom();
    if (polynom.size() != 1) {
      return {};
    }
    return polynom.front();
  }

  void simplifyPow() {
    std::shared_ptr<IMathObject> powSimpl = pow.toMinimalObject();
    pow = SumExpression({});
    pow.addElement(powSimpl);
  }
};

//-----------------------------------------------------------------------------------------------------//

MulExpression::MulExpression(ArgumentsPtrVector children) : IPolynomExpression(MUL, std::move(children)) {
}

std::string MulExpression::sumExprToString(const std::shared_ptr<IMathObject> &obj) {
  if (is<SumExpression>(obj)) {
    return "(" + obj->toString() + ")";
  }
  return obj->toString();
}

std::string MulExpression::toString() const {
  std::string result;

  if (const auto invExpr = cast<InvExpression>(children.front())) {
    result += "1/";
    result += sumExprToString(invExpr->getChildren().front());
  } else {
    result += sumExprToString(children.front());
  }

  for (size_t i = 1; i < children.size(); i++) {
    if (const auto invExpr = cast<InvExpression>(children[i])) {
      result += "/";
      result += sumExprToString(invExpr->getChildren().front());
      continue;
    }
    result += ' ';
    result += sumExprToString(children[i]);
  }

  return result;
}

std::unique_ptr<IMathObject> MulExpression::simplify(bool isPrecise) const {
  // auto exprObj = *this;
  // exprObj.compress();

  // for (auto &obj : exprObj.children) { // TODO: find a better solution
  //   if (is<CompExpression>(obj)) {
  //     throw InvalidInputException(toString());
  //   }
  // }

  // if (exprObj.children.size() == 1) {
  //   simplifyChild(exprObj.children.front());
  //   return exprObj.children.front()->clone();
  // }

  // for (auto &obj : exprObj.children) {
  //   simplifyChild(obj);
  // }

  // exprObj.simplifyDivisions();
  // exprObj.compress();
  // // exprObj.simplifyPolynom();

  // if (exprObj.children.size() == 1) {
  //   simplifyChild(exprObj.children.front());
  //   return exprObj.children.front()->clone();
  // }

  // return exprObj.clone();

  return std::make_unique<MulExpression>(*this);
}

// std::shared_ptr<IMathObject> MulExpression::simplify() {
//   compress();

//   if (children.size() == 1) {
//     simplifyChild(children.front());
//     return children.front();
//   }

//   for (auto &obj : children) {
//     simplifyChild(obj);
//   }

//   simplifyNegations();

//   simplifyPow();

//   simplifyDivisions();

//   simplifyPolynom();

//   if (children.size() == 1) {
//     return children.front();
//   }

//   return shared_from_this();
// }

std::shared_ptr<IMathObject> MulExpression::simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                             const std::shared_ptr<IMathObject> &rhsChild) {

  if (const auto lhsInv = cast<InvExpression>(lhsChild); lhsInv && *lhsInv->getChildren().front() == *rhsChild) {
    return std::make_shared<Integer>(ONE);
  }
  if (const auto rhsInv = cast<InvExpression>(rhsChild); rhsInv && *rhsInv->getChildren().front() == *lhsChild) {
    return std::make_shared<Integer>(ONE);
  }

  return {};
}

void MulExpression::simplifyPow() {
  for (auto &child : children) {
    if (is<PowExpression>(child)) {
      auto powExpr = cast<PowExpression>(child);
      child = powExpr->mulSimplify();
    }
  }
}

void MulExpression::simplifyPolynom() {
  // std::shared_ptr<IMathObject> number = mulNumbers(children);

  // if (*number == ZERO) {
  //   children.clear();
  //   children.emplace_back(number);
  //   return;
  // }

  // ArgumentsPtrVector functions;
  // ArgumentsPtrVector variables;
  // std::map<IOperator::Priority, ArgumentsPtrVector> priorityMap;

  // sortVector(children, priorityMap, functions, variables);
  // simplifyPowCoefficients(priorityMap, functions, variables);

  // ArgumentsPtrVector pows = priorityMap[IOperator::Priority::Exponentiation];
  // for (auto &powExpr : pows) {
  //   auto pow = cast<PowExpression>(powExpr);
  //   powExpr = pow->sumSimplify();
  // }
  // sortVector(pows, priorityMap, functions, variables);

  // children.clear();

  // // TODO: temporary solution
  // for (auto &[key, value] : priorityMap) {
  //   pushPolynomToPolynom(value, children);
  // }
  // pushPolynomToPolynom(functions, children);
  // pushPolynomToPolynom(variables, children);
  // if (children.empty() || *number != Integer(1)) {
  //   children.insert(children.begin(), number);
  // }
}

void MulExpression::simplifyNegations() {
  ArgumentsPtrVector newChildren;
  for (auto &child : children) {
    if (const auto negExpr = cast<NegExpression>(child)) {
      newChildren.emplace_back(NEG_ONE.clone());
      child = negExpr->getChildren().front();
    }
    newChildren.emplace_back(child);
  }
  children = std::move(newChildren);
}

void MulExpression::addValueToMaps(std::shared_ptr<IMathObject> &lhs, std::shared_ptr<IMathObject> &rhs,
                                   std::map<std::string, std::shared_ptr<IMathObject>> &valuesMap,
                                   std::map<std::string, ArgumentsPtrVector> &powMap) {
  powMap[lhs->toString()].emplace_back(rhs);
  if (valuesMap.find(lhs->toString()) == valuesMap.end()) {
    valuesMap[lhs->toString()] = lhs;
  }
}

ArgumentsPtrVector MulExpression::coefficientProcessing(std::map<std::string, std::shared_ptr<IMathObject>> &valuesMap,
                                                        std::map<std::string, ArgumentsPtrVector> &powMap) {
  ArgumentsPtrVector result;
  for (auto &[key, value] : valuesMap) {
    std::shared_ptr<IMathObject> powRhs = std::make_shared<SumExpression>(powMap[key]);
    simplifyChild(powRhs);

    if (const auto number = cast<INumber>(powRhs)) {
      if (*number == ONE) {
        result.emplace_back(value);
        continue;
      }

      if (*number == NEG_ONE) {
        std::shared_ptr<IMathObject> invExpr = std::make_shared<InvExpression>(value);
        simplifyChild(invExpr);
        result.emplace_back(invExpr);
        continue;
      }

      if (*number == ZERO) {
        continue;
      }
    }

    std::shared_ptr<IMathObject> powExpr = std::make_shared<PowExpression>(value, powRhs);
    simplifyChild(powExpr);
    result.emplace_back(powExpr);
  }
  return result;
}

void MulExpression::simplifyPowCoefficients(std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                            ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
  std::map<std::string, std::shared_ptr<IMathObject>> valuesMap;
  std::map<std::string, ArgumentsPtrVector> powMap;

  for (auto &var : variableVector) {
    std::shared_ptr<IMathObject> oneCopy = ONE.clone();
    addValueToMaps(var, oneCopy, valuesMap, powMap);
  }

  for (auto &func : functionVector) {
    if (const auto invFunc = cast<InvExpression>(func)) {
      std::shared_ptr<IMathObject> child = invFunc->getChildren().front();
      std::shared_ptr<IMathObject> negOneCopy = NEG_ONE.clone();
      addValueToMaps(child, negOneCopy, valuesMap, powMap);
      continue;
    }

    std::shared_ptr<IMathObject> oneCopy = ONE.clone();
    addValueToMaps(func, oneCopy, valuesMap, powMap);
  }

  for (auto &[key, value] : priorityMap) {
    if (key != IOperator::Priority::Exponentiation) {
      for (auto &v : value) {
        std::shared_ptr<IMathObject> oneCopy = ONE.clone();
        addValueToMaps(v, oneCopy, valuesMap, powMap);
      }
      continue;
    }
    for (auto &v : value) {
      if (auto powExpr = cast<PowExpression>(v)) {
        std::shared_ptr<IMathObject> lhs = powExpr->getValue();
        std::shared_ptr<IMathObject> rhs = powExpr->getPow();
        addValueToMaps(lhs, rhs, valuesMap, powMap);
      }
    }
  }

  ArgumentsPtrVector vectToSort = coefficientProcessing(valuesMap, powMap);
  priorityMap.clear();
  functionVector.clear();
  variableVector.clear();
  sortVector(vectToSort, priorityMap, functionVector, variableVector);
}

ArgumentsPtrVector MulExpression::multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs) {
  ArgumentsPtrVector result;

  for (const auto &lhsElem : lhs) {
    for (const auto &rhsElem : rhs) {
      auto polynom = cast<MulExpression>(lhsElem)->getPolynom();
      polynom.emplace_back(rhsElem);
      result.emplace_back(std::make_shared<MulExpression>(polynom));
    }
  }

  return result;
}

void MulExpression::multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
                                       ArgumentsPtrVector &negative) {
  ArgumentsPtrVector result;
  ArgumentsPtrVector inverted;
  result.emplace_back(std::make_shared<MulExpression>(ArgumentsPtrVector{ONE.clone()}));
  inverted.emplace_back(std::make_shared<MulExpression>(ArgumentsPtrVector{ONE.clone()}));

  for (const auto &addExpr : addVect) {
  }

  positive = std::move(result);
  negative = std::move(inverted);
}

bool MulExpression::sortFunc(const std::shared_ptr<IMathObject> &lhs, const std::shared_ptr<IMathObject> &rhs) {
  return lhs->toString() < rhs->toString();
}

// TODO: refactor
void MulExpression::sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                                   ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
  /*for (auto &obj : objs) {
    obj.simplifyPow();

    if (auto numObj = obj.getPowIfInteger()) {
      auto num = cast<Integer>(*numObj);

      if (num == ZERO) {
        continue;
      }

      if (is<ILiteral>(obj.obj)) {
        if ((num == 1) || (num == -1)) {
          literalVect.emplace_back(MulElement(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(MulElement(Pow()(*obj.obj, num)));
        continue;
      }

      if (is<Expression>(obj.obj)) {
        if ((num == 1) || (num == -1)) {
          funcVect.emplace_back(MulElement(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(MulElement(Pow()(*obj.obj, num)));
        continue;
      }

      if (is<INumber>(obj.obj)) {
        powVect.emplace_back(MulElement(Pow()(*obj.obj, num)));
        continue;
      }

      auto oldNum = num;
      if (num < 0) {
        num = -num;
      }

      for (Integer i = 0; i < num; i++) {
        addVect.emplace_back(MulElement(obj.obj->clone(), oldNum < 0));
      }

      continue;
    }

    if (auto exprObj = obj.getPowIfSingle()) {
      powVect.emplace_back(MulElement(Pow()(*obj.obj, *exprObj)));
    } else {
      powVect.emplace_back(MulElement(Pow()(*obj.obj, obj.pow)));
    }
  }*/
}

// TODO: refactor
void MulExpression::simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                                ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
  /*Objects objects;
  for (const auto &addObj : addVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == addObj.info->toString()) {
        obj.pow.addElement({ONE.clone(), addObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(addObj.info);
    obj.pow.addElement({ONE.clone(), addObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &litObj : literalVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == litObj.info->toString()) {
        obj.pow.addElement({ONE.clone(), litObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(litObj.info);
    obj.pow.addElement({ONE.clone(), litObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &funcObj : funcVect) {
    bool added = false;
    for (auto &obj : objects) {
      if (obj.obj->toString() == funcObj.info->toString()) {
        obj.pow.addElement({ONE.clone(), funcObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectPow obj(funcObj.info);
    obj.pow.addElement({ONE.clone(), funcObj.inverted});
    objects.emplace_back(obj);
  }

  for (const auto &powObj : powVect) {
    bool added = false;
    const auto *expr = cast<Expression>(powObj.info);

    auto leftValue = expr->getChildren().front()->clone();
    auto rightValue = expr->getChildren().back()->clone();

    for (auto &obj : objects) {
      if (obj.obj->toString() == leftValue->toString()) {
        obj.pow.addElement({rightValue->clone(), powObj.inverted});
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }

    ObjectPow obj(leftValue);
    obj.pow.addElement({rightValue->clone(), powObj.inverted});
    objects.emplace_back(obj);
  }

  powVect.clear();
  literalVect.clear();
  addVect.clear();
  funcVect.clear();

  sortPowObjects(objects, powVect, addVect, literalVect, funcVect);*/
}

void MulExpression::multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive,
                                        ArgumentsPtrVector &negative) {
  /*for (const auto &el : vect) {
    if (el.inverted) {
      negative = multiplicateTwoBraces(negative, {MulElement(el.info->clone())});
    } else {
      positive = multiplicateTwoBraces(positive, {el});
    }
  }*/
}

// TODO: refactor
/*void MulExpression::simplifyPolynom() {
  auto numVect = ArgumentsPtrVector();
  auto powVect = ArgumentsPtrVector();
  auto literalVect = ArgumentsPtrVector();
  auto exprVect = ArgumentsPtrVector();
  auto funcVect = ArgumentsPtrVector();

  // sortPolynom(children, numVect, exprVect, literalVect, funcVect, powVect);
  children.clear();

  // sortPolynom(tmpVect, numVect, exprVect, literalVect, funcVect, powVect);

  numVect = mulNumbers(numVect);
  if (numVect.size() == 1 && *numVect.front() == ZERO) {
    children = std::move(numVect);
    return;
  }

  simplifyPow(powVect, exprVect, literalVect, funcVect);

  ArgumentsPtrVector positive;
  ArgumentsPtrVector negative;

  if (!exprVect.empty()) {
    multiplicateBraces(exprVect, positive, negative);
    // TODO: positive divide by negative
    multiplicatePolynom(literalVect, positive, negative);
    multiplicatePolynom(funcVect, positive, negative);
    multiplicatePolynom(numVect, positive, negative);
    multiplicatePolynom(powVect, positive, negative);

    exprVect.clear();
    numVect.clear();

    bool positiveAdded = false;
    bool negativeAdded = false;
    if (!positive.empty()) {
      auto addExpr = SumExpression(std::move(negative)).toMinimalObject();
      if (!is<INumber>(addExpr)) {
        children.emplace_back(addExpr->clone());
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = SumExpression(std::move(negative)).toMinimalObject();
      if (!is<INumber>(addExpr)) {
        children.emplace_back(InvExpression(addExpr->clone()).toMinimalObject());
        negativeAdded = true;
      } else {
        numVect.emplace_back(InvExpression(addExpr->clone()).toMinimalObject());
      }
    }
    if (positiveAdded && negativeAdded) {
      return;
    }
    numVect = mulNumbers(numVect);
    if (numVect.front()->toString() != "1" || children.empty()) {
      pushPolynomToPolynom(children, numVect);
      children = std::move(numVect);
      return;
    }
    return;
  }

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(exprVect.begin(), exprVect.end(), sortFunc);

  pushPolynomToPolynom(funcVect, children);
  pushPolynomToPolynom(powVect, children);
  pushPolynomToPolynom(exprVect, children);
  pushPolynomToPolynom(literalVect, children);
  if (numVect.front()->toString() != "1" || children.empty()) {
    pushPolynomToPolynom(children, numVect);
    children = std::move(numVect);
  }
}*/

void MulExpression::simplifyDivisions() {
  std::set<size_t> childrenToRemove;

  for (size_t i = 0; i < children.size() - 1; i++) {
    for (size_t j = i + 1; j < children.size(); j++) {
      const auto lhsInv = cast<InvExpression>(children[i]);
      const auto rhsInv = cast<InvExpression>(children[j]);
      if ((lhsInv && *lhsInv->getChildren().front() == *children[j]) ||
          (rhsInv && *rhsInv->getChildren().front() == *children[i])) {
        childrenToRemove.insert(i);
        childrenToRemove.insert(j);
      }
    }
  }

  auto it = childrenToRemove.begin();
  for (size_t i = 0; i < childrenToRemove.size(); i++, ++it) {
    children.erase(children.begin() + int64_t(*it - i));
  }

  if (children.empty()) {
    children.emplace_back(ONE.clone());
  }
}

void MulExpression::setPow(const std::shared_ptr<IMathObject> &value) {
  for (auto &child : children) {
    child = std::make_shared<PowExpression>(child, value);
    simplifyChild(child);
  }
}

// TODO: remove this and implement PowExpression
std::shared_ptr<IMathObject> MulExpression::getPowCoefficient(const std::shared_ptr<IMathObject> &powValue) const {
  /*for (const auto &child : children) {
    if (*powValue == ONE) {
      if (is<Variable>(child)) {
        return children.front()->clone();
      }
    }

    if (const auto *childExpr = cast<Expression>(child); childExpr && is<Pow>(childExpr->getInfo())) {
      if (auto rightVal = childExpr->getChildren().back()->clone(); rightVal && *rightVal == *powValue) {
        return children.front()->clone();
      }
    }
  }*/

  return {};
}

// TODO: remove this and implement PowExpression
std::shared_ptr<IMathObject> MulExpression::getPow() const {
  Integer maxValue = ZERO;

  // TODO: refactor this
  /*for (const auto &child : children) {
    if (const auto *childExpr = cast<Expression>(child); childExpr && is<Pow>(childExpr->getInfo())) {
      if (const auto *pow = cast<Integer>(childExpr->getChildren().back()); *pow > maxValue) {
        maxValue = *pow;
      }
    }
  }*/

  return maxValue.clone();
}

void MulExpression::negate() {
  for (auto &child : children) {
    child = Expression::makeRawFunctionExpression(Neg(), {child});
    simplifyChild(child);
  }
}

void MulExpression::invert() {
  for (auto &child : children) {
    child = Expression::makeRawFunctionExpression(Inv(), {child});
    simplifyChild(child);
  }
}

}
