#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Mul MUL;

MulExpression::MulExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(MUL, children) {
}

// TODO: remove and use operator priority instead
string MulExpression::sumExprToString(const ArgumentPtr &obj) {
  if (const auto expr = cast<IExpression>(obj); expr && is<Add>(expr->getFunction())) {
    return "(" + obj->toString() + ")";
  }
  return obj->toString();
}

string MulExpression::childToString(const ArgumentPtr &child, bool isFirst) const {
  bool invert = false;
  ArgumentPtr childToStr;
  if (auto invExpr = cast<IExpression>(child); invExpr && is<Inv>(invExpr->getFunction())) {
    childToStr = invExpr->getChildren()[0];
    invert = true;
  }
  else {
    childToStr = child;
  }

  string result;
  if (auto sumExpr = cast<IExpression>(childToStr); sumExpr && is<Add>(sumExpr->getFunction())) {
    result = "(" + sumExpr->getChildren()[0]->toString() + ")";
  }
  else {
    result = childToStr->toString();
  }

  if (invert) {
    result = (isFirst ? "1/" : "/") + result;
  }
  else {
    result = (isFirst ? "" : " ") + result;
  }

  return result;
}

// unique_ptr<IMathObject> MulExpression::simplify(bool isPrecise) const {
// auto exprObj = *this;
// exprObj.compress();

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
// }

// ArgumentPtr MulExpression::simplify() {
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

// void MulExpression::simplifyPow() {
//   for (auto &child : children) {
//     if (is<PowExpression>(child)) {
//       auto powExpr = cast<PowExpression>(child);
//       child = powExpr->mulSimplify();
//     }
//   }
// }

// void MulExpression::simplifyPolynom() {
// ArgumentPtr number = mulNumbers(children);

// if (*number == ZERO) {
//   children.clear();
//   children.emplace_back(number);
//   return;
// }

// ArgumentsPtrVector functions;
// ArgumentsPtrVector variables;
// map<IOperator::Priority, ArgumentsPtrVector> priorityMap;

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
// }

// void MulExpression::simplifyNegations() {
//   ArgumentsPtrVector newChildren;
//   for (auto &child : children) {
//     if (const auto negExpr = cast<NegExpression>(child)) {
//       newChildren.emplace_back(NEG_ONE.clone());
//       child = negExpr->getChildren().front();
//     }
//     newChildren.emplace_back(child);
//   }
//   children = move(newChildren);
// }

// void MulExpression::addValueToMaps(ArgumentPtr &lhs, ArgumentPtr &rhs,
//                                    map<string, ArgumentPtr> &valuesMap,
//                                    map<string, ArgumentsPtrVector> &powMap) {
//   powMap[lhs->toString()].emplace_back(rhs);
//   if (valuesMap.find(lhs->toString()) == valuesMap.end()) {
//     valuesMap[lhs->toString()] = lhs;
//   }
// }

// ArgumentsPtrVector MulExpression::coefficientProcessing(map<string, ArgumentPtr>
// &valuesMap,
//                                                         map<string, ArgumentsPtrVector> &powMap) {
//   ArgumentsPtrVector result;
//   for (auto &[key, value] : valuesMap) {
//     ArgumentPtr powRhs = make_shared<SumExpression>(powMap[key]);
//     simplifyChild(powRhs);

//     if (const auto number = cast<INumber>(powRhs)) {
//       if (*number == ONE) {
//         result.emplace_back(value);
//         continue;
//       }

//       if (*number == NEG_ONE) {
//         ArgumentPtr invExpr = make_shared<InvExpression>(value);
//         simplifyChild(invExpr);
//         result.emplace_back(invExpr);
//         continue;
//       }

//       if (*number == ZERO) {
//         continue;
//       }
//     }

//     ArgumentPtr powExpr = make_shared<PowExpression>(value, powRhs);
//     simplifyChild(powExpr);
//     result.emplace_back(powExpr);
//   }
//   return result;
// }

// void MulExpression::simplifyPowCoefficients(map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
//                                             ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
//   map<string, ArgumentPtr> valuesMap;
//   map<string, ArgumentsPtrVector> powMap;

//   for (auto &var : variableVector) {
//     ArgumentPtr oneCopy = ONE.clone();
//     addValueToMaps(var, oneCopy, valuesMap, powMap);
//   }

//   for (auto &func : functionVector) {
//     if (const auto invFunc = cast<InvExpression>(func)) {
//       ArgumentPtr child = invFunc->getChildren().front();
//       ArgumentPtr negOneCopy = NEG_ONE.clone();
//       addValueToMaps(child, negOneCopy, valuesMap, powMap);
//       continue;
//     }

//     ArgumentPtr oneCopy = ONE.clone();
//     addValueToMaps(func, oneCopy, valuesMap, powMap);
//   }

//   for (auto &[key, value] : priorityMap) {
//     if (key != IOperator::Priority::Exponentiation) {
//       for (auto &v : value) {
//         ArgumentPtr oneCopy = ONE.clone();
//         addValueToMaps(v, oneCopy, valuesMap, powMap);
//       }
//       continue;
//     }
//     for (auto &v : value) {
//       if (auto powExpr = cast<PowExpression>(v)) {
//         ArgumentPtr lhs = powExpr->getValue();
//         ArgumentPtr rhs = powExpr->getPow();
//         addValueToMaps(lhs, rhs, valuesMap, powMap);
//       }
//     }
//   }

//   ArgumentsPtrVector vectToSort = coefficientProcessing(valuesMap, powMap);
//   priorityMap.clear();
//   functionVector.clear();
//   variableVector.clear();
//   sortVector(vectToSort, priorityMap, functionVector, variableVector);
// }

// ArgumentsPtrVector MulExpression::multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs)
// {
//   ArgumentsPtrVector result;

//   for (const auto &lhsElem : lhs) {
//     for (const auto &rhsElem : rhs) {
//       auto polynom = cast<MulExpression>(lhsElem)->getPolynom();
//       polynom.emplace_back(rhsElem);
//       result.emplace_back(make_shared<MulExpression>(polynom));
//     }
//   }

//   return result;
// }

// void MulExpression::multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
//                                        ArgumentsPtrVector &negative) {
//   ArgumentsPtrVector result;
//   ArgumentsPtrVector inverted;
//   result.emplace_back(make_shared<MulExpression>(ArgumentsPtrVector{ONE.clone()}));
//   inverted.emplace_back(make_shared<MulExpression>(ArgumentsPtrVector{ONE.clone()}));

//   for (const auto &addExpr : addVect) {
//   }

//   positive = move(result);
//   negative = move(inverted);
// }

// bool MulExpression::sortFunc(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
//   return lhs->toString() < rhs->toString();
// }

// TODO: refactor
// void MulExpression::sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
//  ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
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
// }

// TODO: refactor
// void MulExpression::simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
// ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect) {
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
// }

// void MulExpression::multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive,
// ArgumentsPtrVector &negative) {
/*for (const auto &el : vect) {
  if (el.inverted) {
    negative = multiplicateTwoBraces(negative, {MulElement(el.info->clone())});
  } else {
    positive = multiplicateTwoBraces(positive, {el});
  }
}*/
// }

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
    children = move(numVect);
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
      auto addExpr = SumExpression(move(negative)).toMinimalObject();
      if (!is<INumber>(addExpr)) {
        children.emplace_back(addExpr->clone());
        positiveAdded = true;
      } else {
        numVect.emplace_back(addExpr->clone());
      }
    }
    if (!negative.empty()) {
      auto addExpr = SumExpression(move(negative)).toMinimalObject();
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
      children = move(numVect);
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
    children = move(numVect);
  }
}*/

// void MulExpression::simplifyDivisions() {
//   std::set<size_t> childrenToRemove;

//   for (size_t i = 0; i < children.size() - 1; i++) {
//     for (size_t j = i + 1; j < children.size(); j++) {
//       const auto lhsInv = cast<InvExpression>(children[i]);
//       const auto rhsInv = cast<InvExpression>(children[j]);
//       if ((lhsInv && *lhsInv->getChildren().front() == *children[j]) ||
//           (rhsInv && *rhsInv->getChildren().front() == *children[i])) {
//         childrenToRemove.insert(i);
//         childrenToRemove.insert(j);
//       }
//     }
//   }

//   auto it = childrenToRemove.begin();
//   for (size_t i = 0; i < childrenToRemove.size(); i++, ++it) {
//     children.erase(children.begin() + int64_t(*it - i));
//   }

//   if (children.empty()) {
//     children.emplace_back(ONE.clone());
//   }
// }

// void MulExpression::setPow(const ArgumentPtr &value) {
//   for (auto &child : children) {
//     child = make_shared<PowExpression>(child, value);
//     simplifyChild(child);
//   }
// }

// TODO: remove this and implement PowExpression
// ArgumentPtr MulExpression::getPowCoefficient(const ArgumentPtr &powValue) const {
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

//   return {};
// }

// TODO: remove this and implement PowExpression
// ArgumentPtr MulExpression::getPow() const {
//   Integer maxValue = ZERO;

// TODO: refactor this
/*for (const auto &child : children) {
  if (const auto *childExpr = cast<Expression>(child); childExpr && is<Pow>(childExpr->getInfo())) {
    if (const auto *pow = cast<Integer>(childExpr->getChildren().back()); *pow > maxValue) {
      maxValue = *pow;
    }
  }
}*/

// return maxValue.clone();
// }

ArgumentPtr MulExpression::negate() const {
  MulExpression neg = *this;
  neg.addElement(make_shared<Integer>(NEG_ONE));
  return neg.simplify();
}

ArgumentPtr MulExpression::invert() const {
  auto inv = cast<MulExpression>(clone());

  for (auto &child : inv->children) {
    child = makeFunctionExpression(Inv(), {child});
  }

  return inv->simplify();
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateAndValue(const ArgumentPtr &rhsChild) {
  if (const auto &exprVal = cast<IExpression>(rhsChild); exprVal && is<Pow>(exprVal->getFunction())) {
    ArgumentsPtrVector args = exprVal->getChildren();
    return {args[1], args.front()};
  }

  if (const auto &exprVal = cast<IExpression>(rhsChild); exprVal && is<Inv>(exprVal->getFunction())) {
    ArgumentsPtrVector args = exprVal->getChildren();
    std::pair<ArgumentPtr, ArgumentPtr> result = getRateAndValue(args.front());
    result.first = makeFunctionExpression(Neg(), {result.first});
    return result;
  }

  return {ONE.clone(), rhsChild};
}

ArgumentPtr MulExpression::addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value) {
  ArgumentPtr rateSum = makeFunctionExpression(Add(), rate);
  return makeRawFunctionExpression(Pow(), {value, rateSum});
}

ArgumentPtr MulExpression::simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsInt = cast<Integer>(lhsChild); lhsInt && *lhsInt == ZERO) {
    return lhsChild;
  }
  if (const auto rhsInt = cast<Integer>(rhsChild); rhsInt && *rhsInt == ZERO) {
    return rhsChild;
  }

  if (const auto lhsInt = cast<Integer>(lhsChild); lhsInt && *lhsInt == ONE) {
    return rhsChild;
  }
  if (const auto rhsInt = cast<Integer>(rhsChild); rhsInt && *rhsInt == ONE) {
    return lhsChild;
  }

  bool lhsInv = false;
  bool rhsInv = false;

  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  shared_ptr<const INumber> lhsNum = nullptr;
  shared_ptr<const INumber> rhsNum = nullptr;

  if (lhsExpr && is<Inv>(lhsExpr->getFunction())) {
    lhsInv = true;
    lhsNum = cast<INumber>(lhsExpr->getChildren().front());
  }
  else {
    lhsNum = cast<INumber>(lhsChild);
  }

  if (rhsExpr && is<Inv>(rhsExpr->getFunction())) {
    rhsInv = true;
    rhsNum = cast<INumber>(rhsExpr->getChildren().front());
  }
  else {
    rhsNum = cast<INumber>(rhsChild);
  }

  if (lhsNum && rhsNum) {
    if (lhsInv) {
      return Div()(*rhsNum, *lhsNum);
    }
    if (rhsInv) {
      return Div()(*lhsNum, *rhsNum);
    }
    if (lhsInv && rhsInv) {
      return makeFunctionExpression(Inv(), {Mul()(*lhsNum, *rhsNum)});
    }
    return Mul()(*lhsNum, *rhsNum);
  }

  return nullptr;
}

ArgumentPtr MulExpression::simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Inv>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return make_shared<Integer>(ONE);
  }
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Inv>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return make_shared<Integer>(ONE);
  }

  return {};
}

ArgumentPtr MulExpression::multiplicateBraces(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsVect;
  ArgumentsPtrVector rhsVect;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsVect = lhsExpr->getChildren();
  }
  else {
    lhsVect.emplace_back(lhsChild);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsVect = rhsExpr->getChildren();
  }
  else {
    rhsVect.emplace_back(rhsChild);
  }

  if (lhsVect.size() == 1 && rhsVect.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;
  for (const auto &lhsChildValue : lhsVect) {
    for (const auto &rhsChildValue : rhsVect) {
      resultVect.emplace_back(
          makeFunctionExpression(Mul(), ArgumentsPtrVector{lhsChildValue->clone(), rhsChildValue->clone()}));
    }
  }
  return makeFunctionExpression(Add(), resultVect);
}

ArgumentPtr MulExpression::coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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

ArgumentPtr MulExpression::simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const auto &lhsExpr = cast<IExpression>(lhsChild);
  const auto &rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && is<Neg>(lhsExpr->getFunction()) && is<Neg>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(),
                                  ArgumentsPtrVector{lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});
  }

  return {};
}

MulExpression::FunctionsVector MulExpression::getSimplifyFunctions() const {
  return {&MulExpression::simplifyNegation,       &MulExpression::simplifyNumber,
          &MulExpression::simplifyNegation,       &MulExpression::simplifyDivisions,
          &MulExpression::coefficientsProcessing, &MulExpression::multiplicateBraces};
}

}
