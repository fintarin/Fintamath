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
  std::shared_ptr<IMathObject> obj;
  SumExpression counter = SumExpression({});

  MulObject(std::shared_ptr<IMathObject> obj) : obj(std::move(obj)) {
  }

  void simplifyCounter() {
    std::shared_ptr<IMathObject> counterSimpl = counter.toMinimalObject(); // TODO: remove copy here
    counter = SumExpression({});
    counter.addElement(counterSimpl);
  }

  std::shared_ptr<IMathObject> getCounterValue() const {
    ArgumentsPtrVector polynom = counter.getPolynom();
    const std::shared_ptr<IMathObject> &countValue = polynom.front();
    return is<NegExpression>(polynom.front()) ? Expression::makeFunctionExpression(Neg(), {countValue}) : countValue;
  }
};

SumExpression::SumExpression(ArgumentsPtrVector children) : IPolynomExpression(ADD, std::move(children)) {
}

std::string SumExpression::toString() const {
  std::string result;

  result += children.front()->toString();

  for (size_t i = 1; i < children.size(); i++) {
    std::string childStr = children[i]->toString();

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

std::unique_ptr<IMathObject> SumExpression::simplify(bool isPrecise) const {
  // SumExpression exprObj = *this;
  // exprObj.compress();

  // if (exprObj.children.size() == 1) {
  //   simplifyChild(exprObj.children.front());
  //   return exprObj.children.front()->clone();
  // }

  // for (auto &obj : exprObj.children) {
  //   simplifyChild(obj);
  // }

  // exprObj.compress();
  // // exprObj.simplifyPolynom();

  // if (exprObj.children.size() == 1) {
  //   simplifyChild(exprObj.children.front());
  //   return exprObj.children.front()->clone();
  // }
  // return exprObj.clone();

  return std::make_unique<SumExpression>(*this);
}

bool SumExpression::sortFunc(const std::shared_ptr<IMathObject> &lhs, const std::shared_ptr<IMathObject> &rhs) {
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
  // ArgumentsPtrVector numVect;
  // ArgumentsPtrVector powVect;
  // ArgumentsPtrVector literalVect;
  // ArgumentsPtrVector exprVect;
  // ArgumentsPtrVector funcVect;

  // // sortPolynom(children, numVect, exprVect, literalVect, funcVect, powVect);

  // numVect = sumNumbers(numVect);

  // simplifyMul(powVect, exprVect, literalVect, funcVect);
  // children.clear();

  // std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  // std::sort(powVect.begin(), powVect.end(), sortFunc);
  // std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  // std::sort(exprVect.begin(), exprVect.end(), sortFunc);

  // pushPolynomToPolynom(funcVect, children);
  // pushPolynomToPolynom(powVect, children);
  // pushPolynomToPolynom(exprVect, children);
  // pushPolynomToPolynom(literalVect, children);
  // if (numVect.front()->toString() != "0" || children.empty()) {
  //   pushPolynomToPolynom(numVect, children);
  // }
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
    auto mulExprPolynom = cast<MulExpression>(mulObj)->getArgumentsPtrVector();
    if (mulExprPolynom.empty()) {
      added = true;
    }
    std::unique_ptr<IMathObject> number = ONE.clone();
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
std::shared_ptr<IMathObject> SumExpression::getPowCoefficient(const std::shared_ptr<IMathObject> &powValue) const {
  /*if (*powValue == ZERO) {
    for (const auto &child : children) {
      if (is<INumber>(child.info)) {
        return child.toMathObject(false);
      }
    }
  }

  if (*powValue == ONE) {
    for (const auto &child : children) {
      if (is<Variable>(child.info)) {
        return child.inverted ? NEG_ONE.clone() : ONE.clone();
      }
    }
  }

  for (const auto &child : children) {
    if (const auto *childExpr = cast<MulExpression>(child.info)) {
      if (auto res = childExpr->getPowCoefficient(powValue)) {
        return child.inverted ? Neg()(*res) : res->clone();
      }
    }

    if (const auto *childExpr = cast<Expression>(child.info); childExpr && is<Pow>(childExpr->getInfo())) {
      if (auto rightVal = childExpr->getChildren().back()->clone(); rightVal && *rightVal == *powValue) {
        return child.inverted ? NEG_ONE.clone() : ONE.clone();
      }
    }
  }

  return ZERO.clone();*/
}

// TODO: remove this and implement PowExpression
std::shared_ptr<IMathObject> SumExpression::getPow() const {
  /*auto maxValue = ZERO;

  for (const auto &child : children) {
    if (const auto *childExpr = cast<MulExpression>(child.info)) {
      if (auto childPow = childExpr->getPow()) {
        if (const auto *pow = cast<Integer>(childPow); *pow > maxValue) {
          maxValue = *pow;
        }
      }
    }

    if (const auto *childExpr = cast<Expression>(child.info); childExpr && is<Pow>(childExpr->getInfo())) {
      if (const auto *pow = cast<Integer>(childExpr->getChildren().back()); *pow > maxValue) {
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
  for (auto &child : children) {
    child = Expression::makeRawFunctionExpression(Neg(), {child});
    simplifyChild(child);
  }
}

std::shared_ptr<IMathObject> SumExpression::simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                             const std::shared_ptr<IMathObject> &rhsChild) {

  if (const auto lhsNeg = cast<NegExpression>(lhsChild); lhsNeg && *lhsNeg->getChildren().front() == *rhsChild) {
    return std::make_shared<Integer>(ZERO);
  }
  if (const auto rhsNeg = cast<NegExpression>(rhsChild); rhsNeg && *rhsNeg->getChildren().front() == *lhsChild) {
    return std::make_shared<Integer>(ZERO);
  }

  return {};
}

void SumExpression::multiplicate(const std::shared_ptr<IMathObject> &value) {
}

}
