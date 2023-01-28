#include "fintamath/expressions/MulExpression.hpp"

#include <algorithm>
#include <memory>
#include <set>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
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
    auto polynom = pow.getPolynomVector();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.front().info->clone();
    *powValue = polynom.front().inverted ? *Neg()(*powValue) : *powValue;
    if (is<Integer>(powValue)) {
      return powValue;
    }
    return nullptr;
  }

  MathObjectPtr getPowIfSingle() const {
    auto polynom = pow.getPolynomVector();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.front().info->clone();
    *powValue = polynom.front().inverted ? *Neg()(*powValue) : *powValue;
    return powValue;
  }

  void simplifyPow() {
    pow = SumExpression(*pow.simplify());
  }
};

//-----------------------------------------------------------------------------------------------------//

MulElement::MulElement(const MathObjectPtr &info, bool inverted) : PolynomElement(info, inverted) {
}

MulElement::MulElement(MathObjectPtr &&info, bool inverted) : PolynomElement(info, inverted) {
}

MathObjectPtr MulElement::toMathObject(bool isPrecise) const {
  auto copy = *this;

  if (copy.inverted) {
    copy.info = Expression::buildRawFunctionExpression(Pow(), {*info, NEG_ONE});
    copy.simplify(isPrecise);
    return copy.info->clone();
  }

  copy.simplify(isPrecise);

  return copy.info->clone();
}

void MulElement::simplify(bool isPrecise) {
  if (is<IExpression>(info)) {
    // TODO: remove this condition when polynomial division is implemented
    if (const auto *expr = cast<Expression>(info.get()); expr && is<Pow>(expr->getInfo())) {
      if (auto exprSimpl = expr->simplify(isPrecise); exprSimpl && !is<SumExpression>(exprSimpl)) {
        info = std::move(exprSimpl);
        return;
      }
      return;
    }

    auto expr = cast<IExpression>(std::move(info));
    info = expr->simplify(isPrecise);
    return;
  }

  if (is<IConstant>(info)) {
    auto constant = cast<IConstant>(std::move(info));
    auto constVal = (*constant)();

    if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise() && isPrecise) {
      info = std::move(constant);
    } else {
      info = std::move(constVal);
    }

    return;
  }

  info = info->simplify();
}

//-----------------------------------------------------------------------------------------------------//

MulExpression::MulExpression(PolynomVector inPolynomVect) {
  polynomVect = std::move(inPolynomVect);
  compress();
}

MulExpression::MulExpression(const IMathObject &rhs) {
  if (const auto *rhsPtr = cast<SumExpression>(&rhs)) {
    *this = *rhsPtr;
    return;
  }

  polynomVect.emplace_back(MulElement{rhs.clone(), false});
}

std::string MulExpression::tryPutInBrackets(const MathObjectPtr &obj) {
  if (is<SumExpression>(obj)) {
    return "(" + obj->toString() + ")";
  }
  return tryPutInBracketsIfNeg(obj);
}

std::string MulExpression::toString() const {
  std::string result;

  if (polynomVect.front().inverted) {
    result += "1/";
  }
  result += tryPutInBrackets(polynomVect.front().info);

  for (size_t i = 1; i < polynomVect.size(); i++) {
    result += polynomVect[i].inverted ? '/' : ' ';
    result += tryPutInBrackets(polynomVect[i].info);
  }

  return result;
}

MathObjectPtr MulExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr MulExpression::simplify(bool isPrecise) const {
  auto exprObj = *this;
  exprObj.compress();

  for (auto &obj : exprObj.polynomVect) { // TODO: find a better solution
    if (is<EqvExpression>(obj.info)) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.polynomVect.size() == 1) {
    return exprObj.polynomVect.front().toMathObject(isPrecise);
  }

  for (auto &obj : exprObj.polynomVect) {
    obj.simplify(isPrecise);
  }

  // TODO: find a better solution
  if (!exprObj.polynomVect.empty()) {
    static const Mul func;
    for (size_t i = 0; i < exprObj.polynomVect.size() - 1; i++) {
      validateFunctionArgs(func, {*exprObj.polynomVect.at(i).info, *exprObj.polynomVect.at(i + 1).info});
    }
  }

  exprObj.simplifyDivisions();
  exprObj.compress();
  exprObj.simplifyPolynom();

  if (exprObj.polynomVect.size() == 1) {
    return exprObj.polynomVect.front().toMathObject(isPrecise);
  }

  return exprObj.clone();
}

const IFunction *MulExpression::getFunction() const {
  return &MUL;
}

MulExpression::PolynomVector MulExpression::mulNumbers(const PolynomVector &numVect) {
  Expression result = 1;
  for (const auto &elem : numVect) {
    if (elem.inverted) {
      result.getInfo() = Div()(*result.getInfo(), *elem.info);
    } else {
      result.getInfo() = Mul()(*result.getInfo(), *elem.info);
    }
  }
  return {{result.simplify(), false}};
}

MulExpression::PolynomVector convertAddPolynomToMul(const SumExpression::PolynomVector &polynom) {
  MulExpression::PolynomVector result;

  for (const auto &elem : polynom) {
    result.emplace_back(MulElement(elem.info->clone(), elem.inverted));
  }

  return result;
}

SumExpression::PolynomVector convertMulPolynomToAdd(const MulExpression::PolynomVector &polynom) {
  SumExpression::PolynomVector result;

  for (const auto &elem : polynom) {
    result.emplace_back(SumElement(elem.info->clone(), elem.inverted));
  }

  return result;
}

MulExpression::PolynomVector MulExpression::multiplicateTwoBraces(const PolynomVector &lhs, const PolynomVector &rhs) {
  PolynomVector result;

  for (const auto &lhsElem : lhs) {
    for (const auto &rhsElem : rhs) {
      auto polynom = cast<MulExpression>(lhsElem.info.get())->getPolynomVector();
      polynom.emplace_back(MulElement{rhsElem.info->clone()});
      result.emplace_back(MulElement{std::make_unique<MulExpression>(polynom), lhsElem.inverted != rhsElem.inverted});
    }
  }

  return result;
}

void MulExpression::multiplicateBraces(const PolynomVector &addVect, PolynomVector &positive, PolynomVector &negative) {
  PolynomVector result{MulExpression({ONE}).clone()};
  PolynomVector inverted{MulExpression({ONE}).clone()};

  for (const auto &addExpr : addVect) {
    if (addExpr.inverted) {
      inverted = multiplicateTwoBraces(
          inverted, convertAddPolynomToMul(cast<SumExpression>(addExpr.info.get())->getPolynomVector()));
    } else {
      result = multiplicateTwoBraces(
          result, convertAddPolynomToMul(cast<SumExpression>(addExpr.info.get())->getPolynomVector()));
    }
  }

  positive = result;
  negative = inverted;
}

bool sortFunc(const MulElement &lhs, const MulElement &rhs) {
  return lhs.info->toString() < rhs.info->toString();
}

void MulExpression::sortPowObjects(Objects &objs, PolynomVector &powVect, PolynomVector &addVect,
                                   PolynomVector &literalVect, PolynomVector &funcVect) {
  for (auto &obj : objs) {
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
  }
}

void MulExpression::simplifyPow(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                                PolynomVector &funcVect) {
  Objects objects;
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

  sortPowObjects(objects, powVect, addVect, literalVect, funcVect);
}

void MulExpression::multiplicatePolynom(PolynomVector &vect, PolynomVector &positive, PolynomVector &negative) {
  for (const auto &el : vect) {
    if (el.inverted) {
      negative = multiplicateTwoBraces(negative, {MulElement(el.info->clone())});
    } else {
      positive = multiplicateTwoBraces(positive, {el});
    }
  }
}

void MulExpression::simplifyPolynom() {
  auto numVect = PolynomVector();
  auto powVect = PolynomVector();
  auto literalVect = PolynomVector();
  auto exprVect = PolynomVector();
  auto funcVect = PolynomVector();

  sortPolynom(polynomVect, numVect, exprVect, literalVect, funcVect, powVect);
  polynomVect.clear();

  PolynomVector tmpVect = openPowMulExpression(powVect);
  powVect.clear();

  sortPolynom(tmpVect, numVect, exprVect, literalVect, funcVect, powVect);

  numVect = mulNumbers(numVect);
  if (numVect.size() == 1 && *numVect.front().info == ZERO) {
    polynomVect = numVect;
    return;
  }

  simplifyPow(powVect, exprVect, literalVect, funcVect);

  PolynomVector positive;
  PolynomVector negative;

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
      auto addExpr = SumExpression(convertMulPolynomToAdd(positive)).simplify();
      if (!is<INumber>(addExpr)) {
        polynomVect.emplace_back(MulElement{addExpr->clone()});
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = SumExpression(convertMulPolynomToAdd(negative)).simplify();
      if (!is<INumber>(addExpr)) {
        polynomVect.emplace_back(MulElement(addExpr->clone(), true));
        negativeAdded = true;
      } else {
        numVect.emplace_back(MulElement(addExpr->clone(), true));
      }
    }
    if (positiveAdded && negativeAdded) {
      return;
    }
    numVect = mulNumbers(numVect);
    if (numVect.front().info->toString() != "1" || polynomVect.empty()) {
      pushPolynomToPolynom(polynomVect, numVect);
      polynomVect = numVect;
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
  if (numVect.front().info->toString() != "1" || polynomVect.empty()) {
    pushPolynomToPolynom(polynomVect, numVect);
    polynomVect = numVect;
  }
}

void MulExpression::simplifyDivisions() {
  std::set<size_t> childrenToRemove;

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
  }
}

MulExpression::PolynomVector MulExpression::openPowMulExpression(const PolynomVector &powVect) {
  PolynomVector newPowVect;

  for (const auto &pow : powVect) {
    const auto *expr = cast<Expression>(pow.info.get());
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

  return newPowVect;
}

MathObjectPtr MulExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  for (const auto &child : polynomVect) {
    if (*powValue == ONE) {
      if (is<Variable>(child.info)) {
        return polynomVect.front().info->clone();
      }
    }

    if (const auto *childExpr = cast<Expression>(child.info.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (auto rightVal = childExpr->getChildren().back()->clone(); rightVal && *rightVal == *powValue) {
        return polynomVect.front().info->clone();
      }
    }
  }

  return {};
}

MathObjectPtr MulExpression::getPow() const {
  Integer maxValue = ZERO;

  for (const auto &child : polynomVect) {
    if (const auto *childExpr = cast<Expression>(child.info.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (const auto *pow = cast<Integer>(childExpr->getChildren().back().get()); *pow > maxValue) {
        maxValue = *pow;
      }
    }
  }

  return maxValue.clone();
}

}
