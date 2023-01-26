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

struct MulExpression::ObjectPow {
  MathObjectPtr obj;
  SumExpression pow;

  ObjectPow(const MathObjectPtr &obj) : obj(obj->clone()) {
  }

  ObjectPow(const ObjectPow &objPow) : obj(objPow.obj->clone()), pow(objPow.pow) {
  }

  MathObjectPtr getPowIfInteger() const {
    auto polynom = pow.getPolynom();
    if (polynom.size() != 1) {
      return nullptr;
    }
    auto powValue = polynom.front().info->clone();
    *powValue = polynom.front().inverted ? *Neg()(*powValue) : *powValue;
    if (powValue->instanceOf<Integer>()) {
      return powValue;
    }
    return nullptr;
  }

  MathObjectPtr getPowIfSingle() const {
    auto polynom = pow.getPolynom();
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

MulElement &MulElement::operator=(const MulElement &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
    inverted = rhs.inverted;
  }
  return *this;
}

void MulElement::setPrecision(uint8_t precision) {
  if (info->instanceOf<IExpression>()) {
    auto expr = cast<IExpression>(std::move(info));
    expr->setPrecision(precision);
    info = std::move(expr);
    return;
  }

  if (info->instanceOf<INumber>()) {
    info = Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
  }

  if (info->instanceOf<IConstant>()) {
    auto constVal = (*cast<IConstant>(std::move(info)))();

    if (auto num = cast<INumber>(std::move(constVal))) {
      info = Converter::convert(*num, Real())->to<Real>().precise(precision).clone();
    } else {
      info = std::move(constVal);
    }

    return;
  }
}

MulElement::MulElement(const MathObjectPtr &info, bool inverted) : info(info->clone()), inverted(inverted) {
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

MulElement::MulElement(const MulElement &rhs) : inverted(rhs.inverted) {
  info = rhs.info->clone();
}

void MulElement::simplify(bool isPrecise) {
  if (info->instanceOf<IExpression>()) {
    // TODO: remove this condition when polynomial division is implemented
    if (info->instanceOf<Expression>() && info->to<Expression>().getInfo()->instanceOf<Pow>()) {
      if (auto tmpSimpl = info->to<IExpression>().simplify(isPrecise); !tmpSimpl->instanceOf<SumExpression>()) {
        info = tmpSimpl->clone();
        return;
      }
      return;
    }

    auto expr = cast<IExpression>(std::move(info));
    info = expr->simplify(isPrecise);
    return;
  }

  if (info->instanceOf<IConstant>()) {
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

const MulExpression::PolynomVector &MulExpression::getPolynom() const {
  return mulPolynom;
}

MulExpression::MulExpression(PolynomVector inMulPolynom) : mulPolynom(std::move(inMulPolynom)) {
  compress();
}

MulExpression::MulExpression(const IMathObject &rhs) {
  if (rhs.instanceOf<MulExpression>()) {
    *this = rhs.to<MulExpression>();
    return;
  }
  mulPolynom.emplace_back(MulElement{rhs.clone(), false});
}

uint16_t MulExpression::getBaseOperatorPriority() const {
  return (uint16_t)IOperator::Priority::Multiplication;
}

void MulExpression::setPrecision(uint8_t precision) {
  for (auto &child : mulPolynom) {
    child.setPrecision(precision);
  }
}

void MulExpression::compress() {
  MulExpression compressedExpr;

  for (const auto &child : mulPolynom) {
    compressedExpr.addElement(child);
  }

  *this = std::move(compressedExpr);
}

std::string MulExpression::tryPutInBrackets(const MathObjectPtr &obj) {
  if (obj->instanceOf<SumExpression>()) {
    return "(" + obj->toString() + ")";
  }
  return tryPutInBracketsIfNeg(obj);
}

std::string MulExpression::toString() const {
  std::string result;

  if (mulPolynom.front().inverted) {
    result += "1/";
  }
  result += tryPutInBrackets(mulPolynom.front().info);

  for (size_t i = 1; i < mulPolynom.size(); i++) {
    result += mulPolynom[i].inverted ? '/' : ' ';
    result += tryPutInBrackets(mulPolynom[i].info);
  }

  return result;
}

void MulExpression::addElement(const MulElement &elem) {
  PolynomVector elemPolynom;

  if (const auto *expr = cast<MulExpression>(elem.info.get())) {
    elemPolynom = expr->mulPolynom;
  } else if (const auto *expr = cast<Expression>(elem.info.get())) {
    if (expr->getChildren().empty()) {
      addElement({expr->getInfo(), elem.inverted});
      return;
    }
  }

  if (elemPolynom.empty()) {
    mulPolynom.emplace_back(elem);
    return;
  }

  for (const auto &child : elemPolynom) {
    mulPolynom.emplace_back(child);

    if (elem.inverted) {
      mulPolynom.back().inverted = !mulPolynom.back().inverted;
    }
  }
}

MathObjectPtr MulExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr MulExpression::simplify(bool isPrecise) const {
  auto exprObj = *this;
  exprObj.compress();

  for (auto &obj : exprObj.mulPolynom) { // TODO: find a better solution
    if (obj.info->instanceOf<EqvExpression>()) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.mulPolynom.size() == 1) {
    return exprObj.mulPolynom.front().toMathObject(isPrecise);
  }

  for (auto &obj : exprObj.mulPolynom) {
    obj.simplify(isPrecise);
  }

  if (!exprObj.mulPolynom.empty()) { // TODO: move to PolynomExpression
    static const Mul func;
    for (size_t i = 0; i < exprObj.mulPolynom.size() - 1; i++) {
      validateFunctionArgs(func, {*exprObj.mulPolynom.at(i).info, *exprObj.mulPolynom.at(i + 1).info});
    }
  }

  exprObj.simplifyDivisions();
  exprObj.compress();
  exprObj.simplifyPolynom();

  if (exprObj.mulPolynom.size() == 1) {
    return exprObj.mulPolynom.front().toMathObject(isPrecise);
  }

  return exprObj.clone();
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
    result.emplace_back(SumExpression::SumElement(elem.info->clone(), elem.inverted));
  }
  return result;
}

MulExpression::PolynomVector MulExpression::multiplicateTwoBraces(const PolynomVector &lhs, const PolynomVector &rhs) {
  PolynomVector result;
  for (const auto &lhsElem : lhs) {
    for (const auto &rhsElem : rhs) {
      auto polynom = lhsElem.info->to<MulExpression>().getPolynom();
      polynom.emplace_back(MulElement{rhsElem.info->clone()});
      result.emplace_back(
          MulElement{std::make_unique<MulExpression>(polynom), (bool)(lhsElem.inverted ^ rhsElem.inverted)});
    }
  }
  return result;
}

void MulExpression::multiplicateBraces(const PolynomVector &addVect, PolynomVector &positive, PolynomVector &negative) {
  PolynomVector result{MulExpression({ONE}).clone()};
  PolynomVector inverted{MulExpression({ONE}).clone()};

  for (const auto &addExpr : addVect) {
    if (addExpr.inverted) {
      inverted =
          multiplicateTwoBraces(inverted, convertAddPolynomToMul(addExpr.info->to<SumExpression>().getPolynom()));
    } else {
      result = multiplicateTwoBraces(result, convertAddPolynomToMul(addExpr.info->to<SumExpression>().getPolynom()));
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
      auto num = numObj->to<Integer>();
      if (num == 0) {
        continue;
      }
      if (obj.obj->instanceOf<ILiteral>()) {
        if ((num == 1) || (num == -1)) {
          literalVect.emplace_back(MulElement(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(MulElement(Pow()(*obj.obj, num)));
        continue;
      }

      if (obj.obj->instanceOf<Expression>()) {
        if ((num == 1) || (num == -1)) {
          funcVect.emplace_back(MulElement(obj.obj->clone(), num == -1));
          continue;
        }
        powVect.emplace_back(MulElement(Pow()(*obj.obj, num)));
        continue;
      }

      if (obj.obj->instanceOf<INumber>()) {
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
    auto expr = powObj.info->to<Expression>();

    auto leftValue = expr.getChildren().front()->clone();
    auto rightValue = expr.getChildren().back()->clone();
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

void MulExpression::sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &addVect,
                                PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect) {
  for (const auto &child : vect) {
    if (child.info->instanceOf<SumExpression>()) {
      addVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceOf<Expression>()) {
      if (auto exprInfo = (child.info->to<Expression>()).getInfo()->clone(); exprInfo->instanceOf<Pow>()) {
        powVect.emplace_back(child);
        continue;
      }
      funcVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceOf<IArithmetic>()) {
      numVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceOf<ILiteral>()) {
      literalVect.emplace_back(child);
      continue;
    }
  }
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
  auto addVect = PolynomVector();
  auto funcVect = PolynomVector();

  sortPolynom(mulPolynom, numVect, addVect, literalVect, funcVect, powVect);
  mulPolynom.clear();

  PolynomVector tmpVect = openPowMulExpression(powVect);
  powVect.clear();

  sortPolynom(tmpVect, numVect, addVect, literalVect, funcVect, powVect);

  numVect = mulNumbers(numVect);
  if (numVect.size() == 1 && numVect.front().info->instanceOf<IComparable>() && *numVect.front().info == ZERO) {
    mulPolynom = numVect;
    return;
  }

  simplifyPow(powVect, addVect, literalVect, funcVect);

  PolynomVector positive;
  PolynomVector negative;

  if (!addVect.empty()) {
    multiplicateBraces(addVect, positive, negative);
    // TODO: positive divide by negative
    multiplicatePolynom(literalVect, positive, negative);
    multiplicatePolynom(funcVect, positive, negative);
    multiplicatePolynom(numVect, positive, negative);
    multiplicatePolynom(powVect, positive, negative);

    addVect.clear();
    numVect.clear();

    bool positiveAdded = false;
    bool negativeAdded = false;
    if (!positive.empty()) {
      auto addExpr = SumExpression(convertMulPolynomToAdd(positive)).simplify();
      if (!addExpr->instanceOf<INumber>()) {
        mulPolynom.emplace_back(MulElement{addExpr->clone()});
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = SumExpression(convertMulPolynomToAdd(negative)).simplify();
      if (!addExpr->instanceOf<INumber>()) {
        mulPolynom.emplace_back(MulElement(addExpr->clone(), true));
        negativeAdded = true;
      } else {
        numVect.emplace_back(MulElement(addExpr->clone(), true));
      }
    }
    if (positiveAdded && negativeAdded) {
      return;
    }
    numVect = mulNumbers(numVect);
    if (numVect.front().info->toString() != "1" || mulPolynom.empty()) {
      pushPolynomToPolynom<MulExpression>(mulPolynom, numVect);
      mulPolynom = numVect;
      return;
    }
    return;
  }

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(addVect.begin(), addVect.end(), sortFunc);

  pushPolynomToPolynom<MulExpression>(funcVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(powVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(addVect, mulPolynom);
  pushPolynomToPolynom<MulExpression>(literalVect, mulPolynom);
  if (numVect.front().info->toString() != "1" || mulPolynom.empty()) {
    pushPolynomToPolynom<MulExpression>(mulPolynom, numVect);
    mulPolynom = numVect;
  }
}

void MulExpression::simplifyDivisions() {
  std::set<size_t> childrenToRemove;

  for (size_t i = 0; i < mulPolynom.size() - 1; i++) {
    for (size_t j = i + 1; j < mulPolynom.size(); j++) {
      if (mulPolynom[i].inverted != mulPolynom[j].inverted && *mulPolynom[i].info == *mulPolynom[j].info &&
          childrenToRemove.count(i) == 0 && childrenToRemove.count(j) == 0) {
        childrenToRemove.insert(i);
        childrenToRemove.insert(j);
      }
    }
  }

  auto it = childrenToRemove.begin();
  for (size_t i = 0; i < childrenToRemove.size(); i++, ++it) {
    mulPolynom.erase(mulPolynom.begin() + int64_t(*it - i));
  }

  if (mulPolynom.empty()) {
    mulPolynom.emplace_back(ONE.clone());
  }
}

MulExpression::PolynomVector MulExpression::openPowMulExpression(const PolynomVector &powVect) {
  PolynomVector newPowVect;

  for (const auto &pow : powVect) {
    auto expr = pow.info->to<Expression>();
    auto left = expr.getChildren().front()->clone();
    if (!left->instanceOf<MulExpression>()) {
      newPowVect.emplace_back(pow);
      continue;
    }
    auto right = expr.getChildren().back()->clone();
    auto mulExpr = left->to<MulExpression>();
    for (const auto &child : mulExpr.mulPolynom) {
      newPowVect.emplace_back(MulElement{Pow()(*child.info, *right), child.inverted});
    }
  }
  return newPowVect;
}

std::vector<MathObjectPtr> MulExpression::getVariables() const {
  std::vector<MathObjectPtr> result;
  for (const auto &child : mulPolynom) {
    if (child.info->instanceOf<Variable>()) {
      result.emplace_back(child.info->clone());
      continue;
    }
    if (child.info->instanceOf<IExpression>()) {
      auto addResult = child.info->to<IExpression>().getVariables();
      for (const auto &add : addResult) {
        result.emplace_back(add->clone());
      }
    }
  }
  return result;
}

MathObjectPtr MulExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  for (const auto &child : mulPolynom) {
    if (child.info->instanceOf<Expression>() && child.info->to<Expression>().getInfo()->instanceOf<Pow>()) {
      auto rightVal = child.info->to<Expression>().getChildren().back()->clone();
      if (rightVal->instanceOf<IComparable>() && powValue->instanceOf<IComparable>() && *rightVal == *powValue) {
        return mulPolynom.front().info->clone();
      }
    }
    if (powValue->instanceOf<IComparable>() && *powValue == ONE) {
      if (child.info->instanceOf<Variable>()) {
        return mulPolynom.front().info->clone();
      }
    }
  }
  return nullptr;
}

MathObjectPtr MulExpression::getPow() const {
  Integer maxValue(0);
  for (const auto &child : mulPolynom) {
    if (child.info->instanceOf<Expression>()) {
      if (child.info->to<Expression>().getInfo()->instanceOf<Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().back()->clone();
        if (rightVal->instanceOf<Integer>() && rightVal->to<Integer>() > maxValue) {
          maxValue = rightVal->to<Integer>();
        }
      }
    }
  }
  return maxValue.clone();
}

}
