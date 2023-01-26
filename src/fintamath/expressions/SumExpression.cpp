#include "fintamath/expressions/SumExpression.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <regex>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/Exception.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

struct SumExpression::MulObject {
  MathObjectPtr obj;
  SumExpression counter;

  MulObject(const MathObjectPtr &obj) : obj(obj->clone()) {
  }

  MulObject(const MulObject &objMul) : obj(objMul.obj->clone()), counter(objMul.counter) {
  }

  void simplifyCounter() {
    counter = SumExpression(*counter.simplify());
  }

  MathObjectPtr getCounterValue() const {
    auto polynom = counter.getPolynom();
    auto countValue = polynom.front().info->clone();
    return polynom.front().inverted ? Neg()(*countValue) : std::move(countValue);
  }
};

SumExpression::SumElement::SumElement(const SumElement &rhs) : info(rhs.info->clone()), inverted(rhs.inverted) {
}

SumExpression::SumElement &SumExpression::SumElement::operator=(const SumElement &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
    inverted = rhs.inverted;
  }
  return *this;
}

void SumExpression::SumElement::setPrecision(uint8_t precision) {
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

SumExpression::SumElement::SumElement(const MathObjectPtr &info, bool inverted)
    : info(info->clone()), inverted(inverted) {
}

MathObjectPtr SumExpression::SumElement::toMathObject(bool isPrecise) const {
  auto copy = *this;

  if (copy.inverted) {
    copy.info = Expression::buildRawFunctionExpression(Neg(), {*info});
    copy.simplify(isPrecise);
    return copy.info->clone();
  }

  copy.simplify(isPrecise);

  return copy.info->clone();
}

void SumExpression::SumElement::simplify(bool isPrecise) {
  if (info->instanceOf<IExpression>()) {
    auto expr = cast<IExpression>(std::move(info));
    info = expr->simplify(isPrecise);
    return;
  }

  if (info->instanceOf<IConstant>()) {
    auto constant = cast<IConstant>(std::move(info));
    auto constVal = (*constant)();

    if (const auto *num = cast<INumber>(constVal.get()); isPrecise && !num->isPrecise()) {
      info = std::move(constant);
    } else {
      info = std::move(constVal);
    }

    return;
  }

  info = info->simplify();
}

SumExpression::SumExpression(const IMathObject &rhs) {
  if (const auto *rhsPtr = cast<SumExpression>(&rhs)) {
    *this = *rhsPtr;
    return;
  }

  addPolynom.emplace_back(SumElement{rhs.clone(), false});
}

SumExpression::SumExpression(PolynomVector inAddPolynom) : addPolynom(std::move(inAddPolynom)) {
  compress();
}

uint16_t SumExpression::getBaseOperatorPriority() const {
  return (uint16_t)IOperator::Priority::Addition;
}

void SumExpression::setPrecision(uint8_t precision) {
  for (auto &child : addPolynom) {
    child.setPrecision(precision);
  }
}

std::string SumExpression::toString() const {
  std::string result;

  result += addPolynom.front().info->toString();
  if (result.front() != '-' && addPolynom.front().inverted) {
    result.insert(result.begin(), '-');
  }

  for (size_t i = 1; i < addPolynom.size(); i++) {
    std::string childStr = tryPutInBracketsIfNeg(addPolynom[i].info);

    if (childStr.front() != '-') {
      result += addPolynom[i].inverted ? " - " : " + ";
      result += childStr;
    } else {
      childStr = childStr.substr(1);
      result += addPolynom[i].inverted ? " + " : " - ";
      result += childStr;
    }
  }

  return result;
}

const SumExpression::PolynomVector &SumExpression::getPolynom() const {
  return addPolynom;
}

void SumExpression::compress() {
  SumExpression compressedExpr;

  for (const auto &child : addPolynom) {
    compressedExpr.addElement(child);
  }

  *this = std::move(compressedExpr);
}

void SumExpression::addElement(const SumElement &elem) {
  PolynomVector elemPolynom;

  if (const auto *expr = cast<SumExpression>(elem.info.get())) {
    elemPolynom = expr->addPolynom;
  } else if (const auto *expr = cast<Expression>(elem.info.get())) {
    if (expr->getChildren().empty()) {
      addElement({expr->getInfo(), elem.inverted});
      return;
    }
  }

  if (elemPolynom.empty()) {
    addPolynom.emplace_back(elem);
    return;
  }

  for (const auto &child : elemPolynom) {
    addPolynom.emplace_back(child);

    if (elem.inverted) {
      addPolynom.back().inverted = !addPolynom.back().inverted;
    }
  }
}

MathObjectPtr SumExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr SumExpression::simplify(bool isPrecise) const {
  SumExpression exprObj = *this;
  exprObj.compress();

  for (auto &obj : exprObj.addPolynom) { // TODO: find a better solution
    if (obj.info->instanceOf<EqvExpression>()) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.addPolynom.size() == 1) {
    return exprObj.addPolynom.front().toMathObject(isPrecise);
  }

  for (auto &obj : exprObj.addPolynom) {
    obj.simplify(isPrecise);
  }

  if (!exprObj.addPolynom.empty()) { // TODO: move to PolynomExpression
    static const Add func;
    for (size_t i = 0; i < exprObj.addPolynom.size() - 1; i++) {
      validateFunctionArgs(func, {*exprObj.addPolynom.at(i).info, *exprObj.addPolynom.at(i + 1).info});
    }
  }

  exprObj.simplifyNegations();
  exprObj.compress();
  exprObj.simplifyPolynom();

  if (exprObj.addPolynom.size() == 1) {
    return exprObj.addPolynom.front().toMathObject(isPrecise);
  }
  return exprObj.clone();
}

bool sortFunc(const SumExpression::SumElement &lhs, const SumExpression::SumElement &rhs) {
  if (lhs.info->instanceOf<IConstant>()) {
    return false;
  }

  if (rhs.info->instanceOf<IConstant>()) {
    return true;
  }

  return lhs.info->toString() < rhs.info->toString();
}

void SumExpression::sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &mulVect,
                                PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect) {
  for (const auto &child : vect) {
    if (child.info->instanceOf<MulExpression>()) {
      mulVect.emplace_back(child);
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

void SumExpression::simplifyPolynom() {
  auto numVect = PolynomVector();
  auto powVect = PolynomVector();
  auto literalVect = PolynomVector();
  auto mulVect = PolynomVector();
  auto funcVect = PolynomVector();

  sortPolynom(addPolynom, numVect, mulVect, literalVect, funcVect, powVect);

  numVect = sumNumbers(numVect);

  simplifyMul(powVect, mulVect, literalVect, funcVect);
  addPolynom.clear();

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(mulVect.begin(), mulVect.end(), sortFunc);

  pushPolynomToPolynom<SumExpression>(funcVect, addPolynom);
  pushPolynomToPolynom<SumExpression>(powVect, addPolynom);
  pushPolynomToPolynom<SumExpression>(mulVect, addPolynom);
  pushPolynomToPolynom<SumExpression>(literalVect, addPolynom);
  if (numVect.front().info->toString() != "0" || addPolynom.empty()) {
    pushPolynomToPolynom<SumExpression>(numVect, addPolynom);
  }
}

void SumExpression::simplifyNegations() {
  for (auto &child : addPolynom) {
    if (child.info->instanceOf<Expression>()) {
      auto &childExpr = child.info->to<Expression>();

      if (childExpr.getInfo()->instanceOf<Neg>()) {
        childExpr = Expression(childExpr.getChildren().front());
        child.inverted = !child.inverted;
      }
    }
  }
}

SumExpression::PolynomVector SumExpression::sumNumbers(const PolynomVector &numVect) {
  Expression result;
  for (const auto &elem : numVect) {
    if (elem.inverted) {
      result.getInfo() = Sub()(*result.getInfo(), *elem.info);
    } else {
      result.getInfo() = Add()(*result.getInfo(), *elem.info);
    }
  }
  return {{result.simplify(), false}};
}

void SumExpression::sortMulObjects(MulObjects &objs, PolynomVector &mulVect, PolynomVector &literalVect,
                                   PolynomVector &powVect) {
  for (auto &obj : objs) {
    obj.simplifyCounter();
    auto counter = obj.getCounterValue();
    if (*counter == ZERO) {
      continue;
    }
    if (*counter == ONE || *counter == NEG_ONE) {
      if (obj.obj->instanceOf<ILiteral>()) {
        literalVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
      if (obj.obj->instanceOf<Expression>()) {
        powVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
      if (obj.obj->instanceOf<MulExpression>()) {
        mulVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
    }
    mulVect.emplace_back(SumElement(
        MulExpression({MulExpression::MulElement(obj.obj->clone()), MulExpression::MulElement(counter->clone())})
            .simplify()));
  }
}

void SumExpression::simplifyMul(PolynomVector &powVect, PolynomVector &mulVect, PolynomVector &literalVect,
                                PolynomVector &funcVect) {
  MulObjects objs;
  for (const auto &mulObj : mulVect) {
    bool added = false;
    auto mulExprPolynom = mulObj.info->to<MulExpression>().getPolynom();
    if (mulExprPolynom.empty()) {
      added = true;
    }
    MathObjectPtr number = ONE.clone();
    if (mulExprPolynom.front().info->instanceOf<INumber>()) {
      if (mulExprPolynom.front().inverted) {
        number = Neg()(*mulExprPolynom.front().info);
      } else {
        number = mulExprPolynom.front().info->clone();
      }
      mulExprPolynom = MulExpression::PolynomVector(mulExprPolynom.begin() + 1, mulExprPolynom.end());
    }

    MulExpression mulExpr(mulExprPolynom);
    for (auto &obj : objs) {
      if (obj.obj->toString() == mulExpr.toString()) {
        obj.counter.addElement(SumElement(number->clone(), mulObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    MulObject object(mulExpr.clone());
    object.counter.addElement(SumElement(number->clone(), mulObj.inverted));
    objs.emplace_back(object);
  }
  for (const auto &litObj : literalVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == litObj.info->toString()) {
        obj.counter.addElement(SumElement(ONE.clone(), litObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    MulObject object(litObj.info);
    object.counter.addElement(SumElement(ONE.clone(), litObj.inverted));
    objs.emplace_back(object);
  }
  for (const auto &funcObj : funcVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == funcObj.info->toString()) {
        obj.counter.addElement(SumElement(ONE.clone(), funcObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    MulObject object(funcObj.info);
    object.counter.addElement(SumElement(ONE.clone(), funcObj.inverted));
    objs.emplace_back(object);
  }

  for (const auto &powObj : powVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == powObj.info->toString()) {
        obj.counter.addElement(SumElement(ONE.clone(), powObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    MulObject object(powObj.info);
    object.counter.addElement(SumElement(ONE.clone(), powObj.inverted));
    objs.emplace_back(object);
  }

  literalVect.clear();
  mulVect.clear();
  powVect.clear();
  funcVect.clear();

  sortMulObjects(objs, mulVect, literalVect, powVect);
}

std::vector<MathObjectPtr> SumExpression::getVariables() const {
  std::vector<MathObjectPtr> result;
  for (const auto &child : addPolynom) {
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

MathObjectPtr SumExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  if (powValue->instanceOf<IComparable>() && *powValue == ZERO) {
    for (const auto &child : addPolynom) {
      if (child.info->instanceOf<INumber>()) {
        return child.toMathObject(false);
      }
    }
  }

  if (powValue->instanceOf<IComparable>() && *powValue == ONE) {
    for (const auto &child : addPolynom) {
      if (child.info->instanceOf<Variable>()) {
        return child.inverted ? NEG_ONE.clone() : ONE.clone();
      }
    }
  }

  for (const auto &child : addPolynom) {
    if (child.info->instanceOf<MulExpression>()) {
      if (auto result = child.info->to<MulExpression>().getPowCoefficient(powValue->clone())) {
        return child.inverted ? Neg()(*result) : result->clone();
      }
    }
    if (child.info->instanceOf<Expression>()) {
      if (child.info->to<Expression>().getInfo()->instanceOf<Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().back()->clone();
        if (rightVal->instanceOf<IComparable>() && powValue->instanceOf<IComparable>() && *rightVal == *powValue) {
          return child.inverted ? NEG_ONE.clone() : ONE.clone();
        }
      }
    }
  }
  return ZERO.clone();
}

MathObjectPtr SumExpression::getPow() const {
  auto maxValue = ZERO;
  for (const auto &child : addPolynom) {
    if (child.info->instanceOf<MulExpression>()) {
      auto pow = child.info->to<MulExpression>().getPow();
      if (pow->instanceOf<Integer>() && pow->to<Integer>() > maxValue) {
        maxValue = pow->to<Integer>();
      }
    }
    if (child.info->instanceOf<Expression>()) {
      if (child.info->to<Expression>().getInfo()->instanceOf<Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().back()->clone();
        if (rightVal->instanceOf<Integer>() && rightVal->to<Integer>() > maxValue) {
          maxValue = rightVal->to<Integer>();
        }
      }
    }
    if (child.info->instanceOf<Variable>()) {
      if (ONE > maxValue) {
        maxValue = ONE;
      }
    }
  }
  return maxValue.clone();
}

}