#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <regex>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/Exception.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

const Add ADD;

struct SumExpression::MulObject {
  MathObjectPtr obj;
  SumExpression counter;

  MulObject(const MathObjectPtr &obj) : obj(obj->clone()) {
  }

  MulObject(const MulObject &objMul) : obj(objMul.obj->clone()), counter(objMul.counter) {
  }

  void simplifyCounter() {
    auto counterSimpl = counter.toMinimalObject();
    counter = SumExpression();
    counter.addElement(std::move(counterSimpl));
  }

  MathObjectPtr getCounterValue() const {
    auto polynom = counter.clonePolynom();
    auto countValue = polynom.front()->clone();
    return is<NegExpression>(polynom.front()) ? Neg()(*countValue) : std::move(countValue);
  }
};

SumExpression::SumExpression(ArgumentsPtrVector &&inPolynomVect) : IPolynomExpression(std::move(inPolynomVect)) {
  if (!polynomVect.empty()) {
    compress();
  }
}

std::string SumExpression::toString() const {
  std::string result;

  result += polynomVect.front()->toString();

  for (size_t i = 1; i < polynomVect.size(); i++) {
    std::string childStr = polynomVect[i]->toString();

    if (childStr.front() != '-') {
      result += " + ";
      result += childStr;
    } else {
      childStr = childStr.substr(1);
      result += " - ";
      result += childStr;
    }
  }

  return result;
}

MathObjectPtr SumExpression::simplify(bool isPrecise) const {
  SumExpression exprObj = *this;
  exprObj.compress();

  for (auto &obj : exprObj.polynomVect) { // TODO: find a better solution
    if (is<CompExpression>(obj)) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.polynomVect.size() == 1) {
    simplifyExpr(exprObj.polynomVect.front());
    return exprObj.polynomVect.front()->clone();
  }

  for (auto &obj : exprObj.polynomVect) {
    simplifyExpr(obj);
  }

  exprObj.compress();
  // exprObj.simplifyPolynom();

  if (exprObj.polynomVect.size() == 1) {
    simplifyExpr(exprObj.polynomVect.front());
    return exprObj.polynomVect.front()->clone();
  }
  return exprObj.clone();
}

const IFunction *SumExpression::getFunction() const {
  return &ADD;
}

bool SumExpression::sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs) {
  if (is<IConstant>(lhs)) {
    return false;
  }

  if (is<IConstant>(rhs)) {
    return true;
  }

  return lhs->toString() < rhs->toString();
}

// TODO: refactor
void SumExpression::simplifyPolynom() {
  auto numVect = ArgumentsPtrVector();
  auto powVect = ArgumentsPtrVector();
  auto literalVect = ArgumentsPtrVector();
  auto exprVect = ArgumentsPtrVector();
  auto funcVect = ArgumentsPtrVector();

  // sortPolynom(polynomVect, numVect, exprVect, literalVect, funcVect, powVect);

  numVect = sumNumbers(numVect);

  simplifyMul(powVect, exprVect, literalVect, funcVect);
  polynomVect.clear();

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(exprVect.begin(), exprVect.end(), sortFunc);

  pushPolynomToPolynom(funcVect, polynomVect);
  pushPolynomToPolynom(powVect, polynomVect);
  pushPolynomToPolynom(exprVect, polynomVect);
  pushPolynomToPolynom(literalVect, polynomVect);
  if (numVect.front()->toString() != "0" || polynomVect.empty()) {
    pushPolynomToPolynom(numVect, polynomVect);
  }
}

ArgumentsPtrVector SumExpression::sumNumbers(const ArgumentsPtrVector &numVect) {
  Expression result;
  ArgumentsPtrVector resultVector;
  for (const auto &elem : numVect) {
    result.getInfo() = Add()(*result.getInfo(), *elem);
  }
  resultVector.emplace_back(result.toMinimalObject());
  return resultVector;
}

// TODO: refactor
void SumExpression::sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
                                   ArgumentsPtrVector &powVect) {
  /*for (auto &obj : objs) {
    obj.simplifyCounter();
    auto counter = obj.getCounterValue();
    if (*counter == ZERO) {
      continue;
    }
    if (*counter == ONE || *counter == NEG_ONE) {
      if (is<ILiteral>(obj.obj)) {
        literalVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
      if (is<Expression>(obj.obj)) {
        powVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
      if (is<MulExpression>(obj.obj)) {
        mulVect.emplace_back(obj.obj->clone(), *counter == NEG_ONE);
        continue;
      }
    }
    mulVect.emplace_back(MulExpression({{obj.obj->clone()}, {counter->clone()}}).toMinimalObject());
  }*/
}

// TODO: refactor
void SumExpression::simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &mulVect,
                                ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
  /*MulObjects objs;
  for (const auto &mulObj : mulVect) {
    bool added = false;
    auto mulExprPolynom = cast<MulExpression>(mulObj.get())->getArgumentsPtrVector();
    if (mulExprPolynom.empty()) {
      added = true;
    }
    MathObjectPtr number = ONE.clone();
    if (is<INumber>(mulExprPolynom.front())) {
      if (mulExprPolynom.front().inverted) {
        number = Neg()(*mulExprPolynom.front());
      } else {
        number = mulExprPolynom.front()->clone();
      }
      mulExprPolynom = MulExpression::ArgumentsPtrVector(mulExprPolynom.begin() + 1, mulExprPolynom.end());
    }

    MulExpression mulExpr(mulExprPolynom);
    for (auto &obj : objs) {
      if (obj.obj->toString() == mulExpr.toString()) {
        obj.counter.addElement(number->clone());
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
    MulObject object(powObj);
    object.counter.addElement(SumElement(ONE.clone(), powObj.inverted));
    objs.emplace_back(object);
  }

  literalVect.clear();
  mulVect.clear();
  powVect.clear();
  funcVect.clear();

  sortMulObjects(objs, mulVect, literalVect, powVect);*/
}

// TODO: remove this and implement PowExpression
MathObjectPtr SumExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  /*if (*powValue == ZERO) {
    for (const auto &child : polynomVect) {
      if (is<INumber>(child.info)) {
        return child.toMathObject(false);
      }
    }
  }

  if (*powValue == ONE) {
    for (const auto &child : polynomVect) {
      if (is<Variable>(child.info)) {
        return child.inverted ? NEG_ONE.clone() : ONE.clone();
      }
    }
  }

  for (const auto &child : polynomVect) {
    if (const auto *childExpr = cast<MulExpression>(child.info.get())) {
      if (auto res = childExpr->getPowCoefficient(powValue)) {
        return child.inverted ? Neg()(*res) : res->clone();
      }
    }

    if (const auto *childExpr = cast<Expression>(child.info.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (auto rightVal = childExpr->getChildren().back()->clone(); rightVal && *rightVal == *powValue) {
        return child.inverted ? NEG_ONE.clone() : ONE.clone();
      }
    }
  }

  return ZERO.clone();*/
}

// TODO: remove this and implement PowExpression
MathObjectPtr SumExpression::getPow() const {
  /*auto maxValue = ZERO;

  for (const auto &child : polynomVect) {
    if (const auto *childExpr = cast<MulExpression>(child.info.get())) {
      if (auto childPow = childExpr->getPow()) {
        if (const auto *pow = cast<Integer>(childPow.get()); *pow > maxValue) {
          maxValue = *pow;
        }
      }
    }

    if (const auto *childExpr = cast<Expression>(child.info.get()); childExpr && is<Pow>(childExpr->getInfo())) {
      if (const auto *pow = cast<Integer>(childExpr->getChildren().back().get()); *pow > maxValue) {
        maxValue = *pow;
      }
    }

    if (is<Variable>(child.info)) {
      if (ONE > maxValue) {
        maxValue = ONE;
      }
    }
  }

  return maxValue.clone();*/
  return {};
}

void SumExpression::negate() {
  for (auto &child : polynomVect) {
    child = std::make_unique<NegExpression>(std::move(child));
    simplifyExpr(child);
  }
}

IMathObject *SumExpression::simplify() {
  return this;
}

}