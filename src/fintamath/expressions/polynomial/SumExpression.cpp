#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
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

// unique_ptr<IMathObject> SumExpression::simplify(bool isPrecise) const {
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
// }

// bool SumExpression::sortFunc(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
//   if (is<IConstant>(lhs)) {
//     return false;
//   }

//   if (is<IConstant>(rhs)) {
//     return true;
//   }

//   return lhs->toString() < rhs->toString();
// }

// TODO: refactor
// void SumExpression::simplifyPolynom() {
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
// }

// TODO: refactor
// void SumExpression::sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
//  ArgumentsPtrVector &powVect) {
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
// }

// TODO: refactor
// void SumExpression::simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &mulVect,
// ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
/*MulObjects objs;
for (const auto &mulObj : mulVect) {
  bool added = false;
  auto mulExprPolynom = cast<MulExpression>(mulObj)->getArgumentsPtrVector();
  if (mulExprPolynom.empty()) {
    added = true;
  }
  unique_ptr<IMathObject> number = ONE.clone();
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
// }

// TODO: remove this and implement PowExpression
// ArgumentPtr SumExpression::getPowCoefficient(const ArgumentPtr &powValue) const {
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
// }

// TODO: remove this and implement PowExpression
// ArgumentPtr SumExpression::getPow() const {
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
// }

// void SumExpression::multiplicate(const ArgumentPtr &value) {
// }

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
    lhsNeg = true;
    lhsNum = cast<INumber>(lhsExpr->getChildren().front());
  }
  else {
    lhsNum = cast<INumber>(lhsChild);
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    rhsNeg = true;
    rhsNum = cast<INumber>(rhsExpr->getChildren().front());
  }
  else {
    rhsNum = cast<INumber>(rhsChild);
  }

  if (lhsNum && rhsNum) {
    if (lhsNeg) {
      return Sub()(*rhsNum, *lhsNum);
    }
    if (rhsNeg) {
      return Sub()(*lhsNum, *rhsNum);
    }
    if (lhsNeg && rhsNeg) {
      return makeFunctionExpression(Neg(), {Add()(*lhsNum, *rhsNum)});
    }
    return Add()(*lhsNum, *rhsNum);
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
}
