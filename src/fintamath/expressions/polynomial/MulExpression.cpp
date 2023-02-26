#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <memory>
#include <set>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

const Mul MUL;

struct MulExpression::ObjectPow {
  MathObjectPtr obj;
  SumExpression pow;

  ObjectPow(const MathObjectPtr &obj) : obj(obj->clone()) {
  }

  ObjectPow(const ObjectPow &objPow) : obj(objPow.obj->clone()), pow(objPow.pow) {
  }

  MathObjectPtr getPowIfInteger() const {
    auto polynom = pow.clonePolynom();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.front()->toMinimalObject();
    if (is<Integer>(powValue)) {
      return powValue;
    }
    return nullptr;
  }

  MathObjectPtr getPowIfSingle() const {
    auto polynom = pow.clonePolynom();
    if (polynom.size() != 1) {
      return nullptr;
    }
    return polynom.front()->clone();
  }

  void simplifyPow() {
    auto powSimpl = pow.toMinimalObject();
    pow = SumExpression();
    pow.addElement(std::move(powSimpl));
  }
};

//-----------------------------------------------------------------------------------------------------//

MulExpression::MulExpression(ArgumentsPtrVector &&inPolynomVect) : IPolynomExpression(std::move(inPolynomVect)) {
  if (!polynomVect.empty()) {
    compress();
  }
}

std::string MulExpression::sumExprToString(const MathObjectPtr &obj) {
  if (is<SumExpression>(obj)) {
    return "(" + obj->toString() + ")";
  }
  return obj->toString();
}

std::string MulExpression::toString() const {
  std::string result;

  if (const auto *invExpr = cast<InvExpression>(polynomVect.front().get())) {
    result += "1 / ";
    result += sumExprToString(invExpr->getInfo());
  } else {
    result += sumExprToString(polynomVect.front());
  }

  for (size_t i = 1; i < polynomVect.size(); i++) {
    if (const auto *invExpr = cast<InvExpression>(polynomVect.front().get())) {
      result += " / ";
      result += sumExprToString(invExpr->getInfo());
      continue;
    }
    result += ' ';
    result += sumExprToString(polynomVect[i]);
  }

  return result;
}

MathObjectPtr MulExpression::toMinimalObject() const {
  return simplify(true);
}

MathObjectPtr MulExpression::simplify(bool isPrecise) const {
  auto exprObj = *this;
  exprObj.compress();

  for (auto &obj : exprObj.polynomVect) { // TODO: find a better solution
    if (is<CompExpression>(obj)) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.polynomVect.size() == 1) {
    simplifyValue(isPrecise, exprObj.polynomVect.front());
    return exprObj.polynomVect.front()->clone();
  }

  for (auto &obj : exprObj.polynomVect) {
    simplifyValue(isPrecise, obj);
  }

  exprObj.simplifyDivisions();
  exprObj.compress();
  // exprObj.simplifyPolynom();

  if (exprObj.polynomVect.size() == 1) {
    simplifyValue(isPrecise, exprObj.polynomVect.front());
    return exprObj.polynomVect.front()->clone();
  }

  return exprObj.clone();
}

const IFunction *MulExpression::getFunction() const {
  return &MUL;
}

ArgumentsPtrVector MulExpression::mulNumbers(const ArgumentsPtrVector &numVect) {
  Expression result = 1;
  ArgumentsPtrVector resultVector;
  for (const auto &elem : numVect) {
    result.getInfo() = Mul()(*result.getInfo(), *elem);
  }
  resultVector.emplace_back(result.toMinimalObject());
  return resultVector;
}

ArgumentsPtrVector MulExpression::multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs) {
  ArgumentsPtrVector result;

  for (const auto &lhsElem : lhs) {
    for (const auto &rhsElem : rhs) {
      auto polynom = cast<MulExpression>(lhsElem.get())->clonePolynom();
      polynom.emplace_back(rhsElem->clone());
      result.emplace_back(std::make_unique<MulExpression>(std::move(polynom)));
    }
  }

  return result;
}

void MulExpression::multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
                                       ArgumentsPtrVector &negative) {
  ArgumentsPtrVector result;
  ArgumentsPtrVector inverted;
  result.emplace_back(std::make_unique<MulExpression>(makeArgumentsPtrVector(ONE.clone())));
  inverted.emplace_back(std::make_unique<MulExpression>(makeArgumentsPtrVector(ONE.clone())));

  for (const auto &addExpr : addVect) {
  }

  positive = std::move(result);
  negative = std::move(inverted);
}

bool MulExpression::sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs) {
  return lhs->toString() < rhs->toString();
}

// TODO: refactor
void MulExpression::sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                                   ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
  /*for (auto &obj : objs) {
    obj.simplifyPow();

    if (auto numObj = obj.getPowIfInteger()) {
      auto num = cast<Integer>(*numObj.get());

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
    const auto *expr = cast<Expression>(powObj.info.get());

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
void MulExpression::simplifyPolynom() {
  auto numVect = ArgumentsPtrVector();
  auto powVect = ArgumentsPtrVector();
  auto literalVect = ArgumentsPtrVector();
  auto exprVect = ArgumentsPtrVector();
  auto funcVect = ArgumentsPtrVector();

  // sortPolynom(polynomVect, numVect, exprVect, literalVect, funcVect, powVect);
  polynomVect.clear();

  ArgumentsPtrVector tmpVect = openPowMulExpression(powVect);
  powVect.clear();

  // sortPolynom(tmpVect, numVect, exprVect, literalVect, funcVect, powVect);

  numVect = mulNumbers(numVect);
  if (numVect.size() == 1 && *numVect.front() == ZERO) {
    polynomVect = std::move(numVect);
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
        polynomVect.emplace_back(addExpr->clone());
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = SumExpression(std::move(negative)).toMinimalObject();
      if (!is<INumber>(addExpr)) {
        polynomVect.emplace_back(InvExpression(addExpr->clone()).toMinimalObject());
        negativeAdded = true;
      } else {
        numVect.emplace_back(InvExpression(addExpr->clone()).toMinimalObject());
      }
    }
    if (positiveAdded && negativeAdded) {
      return;
    }
    numVect = mulNumbers(numVect);
    if (numVect.front()->toString() != "1" || polynomVect.empty()) {
      pushPolynomToPolynom(polynomVect, numVect);
      polynomVect = std::move(numVect);
      return;
    }
    return;
  }

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(exprVect.begin(), exprVect.end(), sortFunc);

  pushPolynomToPolynom(funcVect, polynomVect);
  pushPolynomToPolynom(powVect, polynomVect);
  pushPolynomToPolynom(exprVect, polynomVect);
  pushPolynomToPolynom(literalVect, polynomVect);
  if (numVect.front()->toString() != "1" || polynomVect.empty()) {
    pushPolynomToPolynom(polynomVect, numVect);
    polynomVect = std::move(numVect);
  }
}

void MulExpression::simplifyDivisions() {
  /*std::set<size_t> childrenToRemove;

  for (size_t i = 0; i < polynomVect.size() - 1; i++) {
    for (size_t j = i + 1; j < polynomVect.size(); j++) {
      if (polynomVect[i].inverted != polynomVect[j].inverted && *polynomVect[i].info == *polynomVect[j].info &&
          childrenToRemove.count(i) == 0 && childrenToRemove.count(j) == 0) {
        childrenToRemove.insert(i);
        childrenToRemove.insert(j);
      }
    }
  }

  auto it = childrenToRemove.begin();
  for (size_t i = 0; i < childrenToRemove.size(); i++, ++it) {
    polynomVect.erase(polynomVect.begin() + int64_t(*it - i));
  }

  if (polynomVect.empty()) {
    polynomVect.emplace_back(ONE.clone());
  }*/
}

ArgumentsPtrVector MulExpression::openPowMulExpression(const ArgumentsPtrVector &powVect) {
  /*ArgumentsPtrVector newPowVect;

  for (const auto &pow : powVect) {
    const auto *expr = cast<Expression>(pow.get());
    auto left = expr->getChildren().front()->clone();

    if (!is<MulExpression>(left)) {
      newPowVect.emplace_back(pow);
      continue;
    }

    auto right = expr->getChildren().back()->clone();
    const auto *mulExpr = cast<MulExpression>(left.get());

    for (const auto &child : mulExpr->polynomVect) {
      newPowVect.emplace_back(MulElement{Pow()(*child.info, *right), child.inverted});
    }
  }

  return newPowVect;*/
  return {};
}

// TODO: remove this and implement PowExpression
MathObjectPtr MulExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  /*for (const auto &child : polynomVect) {
    if (*powValue == ONE) {
      if (is<Variable>(child)) {
        return polynomVect.front()->clone();
      }
    }

    if (const auto *childExpr = cast<Expression>(child.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (auto rightVal = childExpr->getChildren().back()->clone(); rightVal && *rightVal == *powValue) {
        return polynomVect.front()->clone();
      }
    }
  }*/

  return {};
}

// TODO: remove this and implement PowExpression
MathObjectPtr MulExpression::getPow() const {
  Integer maxValue = ZERO;

  // TODO: refactor this
  /*for (const auto &child : polynomVect) {
    if (const auto *childExpr = cast<Expression>(child.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (const auto *pow = cast<Integer>(childExpr->getChildren().back().get()); *pow > maxValue) {
        maxValue = *pow;
      }
    }
  }*/

  return maxValue.clone();
}

void MulExpression::negate() {
  if (polynomVect.empty()) {
    return;
  }
  polynomVect.front() = NegExpression(std::move(polynomVect.front())).toMinimalObject();
}

void MulExpression::invert() {
  for (auto &child : polynomVect) {
    child = InvExpression(std::move(child)).toMinimalObject();
  }
}

}
