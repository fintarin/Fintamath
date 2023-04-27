#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Mul MUL;

MulExpression::MulExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(MUL, children) {
}

// string MulExpression::toString() const {
//   ArgumentsPtrVector mulChildren;
//   ArgumentsPtrVector divChildren;

//   for (const auto &child : children) {
//     if (const auto &childExpr = cast<IExpression>(child); childExpr && is<Inv>(childExpr->getFunction())) {
//       divChildren.emplace_back(child);
//     }
//     else {
//       mulChildren.emplace_back(child);
//     }
//   }

//   string result;

//   switch (mulChildren.size()) {
//   case 0: {
//     result += childToString(divChildren.front(), true);

//     for (size_t i = 1; i < divChildren.size(); i++) {
//       result += childToString(divChildren[i]);
//     }

//     break;
//   }
//   case 1: {
//     result += childToString(mulChildren.front(), true);

//     for (const auto &child : divChildren) {
//       result += childToString(child);
//     }

//     break;
//   }
//   default: {
//     result += childToString(mulChildren.front(), true);

//     for (size_t i = 1; i < mulChildren.size(); i++) {
//       result += childToString(mulChildren[i], result == Neg().toString());
//     }

//     if (!divChildren.empty()) {
//       result = putInBrackets(result);
//     }

//     for (const auto &child : divChildren) {
//       result += childToString(child);
//     }

//     break;
//   }
//   }

//   return result;
// }

string MulExpression::childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  if (!prevChild && *inChild == NEG_ONE) {
    return Neg().toString();
  }

  ArgumentPtr child = inChild;
  // bool isChildInverted = false;

  // if (auto invExpr = cast<IExpression>(inChild); invExpr && is<Inv>(invExpr->getFunction())) {
  //   child = invExpr->getChildren().front();
  //   isChildInverted = true;
  // }

  string result;

  if (auto sumExpr = cast<IExpression>(child); sumExpr && is<Add>(sumExpr->getFunction())) {
    result = putInBrackets(sumExpr->toString());
  }
  else {
    result = child->toString();
  }

  // if (isChildInverted) {
  // result = (isFirst ? ONE.toString() : "") + Div().toString() + result;
  // }
  // else {
  result = (prevChild && *prevChild != NEG_ONE ? " " : "") + result;
  // }

  return result;
}

ArgumentPtr MulExpression::negate() const {
  MulExpression mulExpr = *this;
  mulExpr.addElement(NEG_ONE.clone());
  return mulExpr.simplify();
}

// ArgumentPtr MulExpression::invert() const {
//   auto mulExpr = cast<MulExpression>(clone());

//   for (auto &child : mulExpr->children) {
//     child = makeFunctionExpression(Inv(), {child});
//   }

//   return mulExpr->simplify();
// }

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateValuePair(const ArgumentPtr &rhsChild) {
  if (const auto &powExpr = cast<IExpression>(rhsChild); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren.front()};
  }

  // if (const auto &invExpr = cast<IExpression>(rhsChild); invExpr && is<Inv>(invExpr->getFunction())) {
  //   ArgumentsPtrVector invExprChildren = invExpr->getChildren();
  //   std::pair<ArgumentPtr, ArgumentPtr> result = getRateValuePair(invExprChildren.front());
  //   result.first = makeFunctionExpression(Neg(), {result.first});
  //   return result;
  // }

  return {ONE.clone(), rhsChild};
}

ArgumentPtr MulExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeFunctionExpression(Add(), rates);
  return makeRawFunctionExpression(Pow(), {value, ratesSum});
}

ArgumentPtr MulExpression::simplifyNumbers(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == ZERO) {
    return lhsChild;
  }
  if (*rhsChild == ZERO) {
    return rhsChild;
  }

  if (*lhsChild == ONE) {
    return rhsChild;
  }
  if (*rhsChild == ONE) {
    return lhsChild;
  }

  // bool isLhsInverted = false;
  // bool isRhsInverted = false;

  // const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  // const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  shared_ptr<const INumber> lhsNum = nullptr;
  shared_ptr<const INumber> rhsNum = nullptr;

  // if (lhsExpr && is<Inv>(lhsExpr->getFunction())) {
  //   isLhsInverted = true;
  //   lhsNum = cast<INumber>(lhsExpr->getChildren().front());
  // }
  // else {
  lhsNum = cast<INumber>(lhsChild);
  // }

  // if (rhsExpr && is<Inv>(rhsExpr->getFunction())) {
  // isRhsInverted = true;
  // rhsNum = cast<INumber>(rhsExpr->getChildren().front());
  // }
  // else {
  rhsNum = cast<INumber>(rhsChild);
  // }

  if (lhsNum && rhsNum) {
    // if (isLhsInverted && isRhsInverted) {
    // return Inv()(*Mul()(*lhsNum, *rhsNum));
    // }

    // if (isLhsInverted) {
    //   return Div()(*rhsNum, *lhsNum);
    // }

    // if (isRhsInverted) {
    //   return Div()(*lhsNum, *rhsNum);
    // }

    return Mul()(*lhsNum, *rhsNum);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  bool isLhsDiv = false;
  bool isRhsDiv = false;

  if (lhsExpr && is<Div>(lhsExpr->getFunction())) {
    isLhsDiv = true;
  }

  if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    isRhsDiv = true;
  }

  ArgumentPtr numerator;
  ArgumentPtr denominator;

  if (isLhsDiv && isRhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});
    denominator = makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().back(), rhsExpr->getChildren().back()});
  }
  else if (isLhsDiv) {
    numerator = rhsChild;
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = lhsChild;
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  return makeFunctionExpression(Div(), {numerator, denominator});
}

ArgumentPtr MulExpression::mulPolynoms(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  // bool isResultInverted = false;

  ArgumentPtr lhs = lhsChild;
  ArgumentPtr rhs = rhsChild;

  shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  // if (lhsExpr && rhsExpr && is<Inv>(lhsExpr->getFunction()) && is<Inv>(rhsExpr->getFunction())) {
  //   isResultInverted = true;

  //   lhs = lhsExpr->getChildren().front();
  //   rhs = rhsExpr->getChildren().front();

  //   lhsExpr = cast<IExpression>(lhs);
  //   rhsExpr = cast<IExpression>(rhs);
  // }

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhs);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhs);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;

  for (const auto &lhsChild : lhsChildren) {
    for (const auto &rhsChild : rhsChildren) {
      resultVect.emplace_back(makeFunctionExpression(Mul(), ArgumentsPtrVector{lhsChild->clone(), rhsChild->clone()}));
    }
  }

  // if (isResultInverted) {
  //   return makeFunctionExpression(Inv(), {makeFunctionExpression(Add(), resultVect)});
  // }

  return makeFunctionExpression(Add(), resultVect);
}

ArgumentPtr MulExpression::mulRates(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::pair<ArgumentPtr, ArgumentPtr> lhsRateValue = getRateValuePair(lhsChild);
  std::pair<ArgumentPtr, ArgumentPtr> rhsRateValue = getRateValuePair(rhsChild);

  ArgumentPtr lhsChildRate = lhsRateValue.first;
  ArgumentPtr rhsChildRate = rhsRateValue.first;

  ArgumentPtr lhsChildValue = lhsRateValue.second;
  ArgumentPtr rhsChildValue = rhsRateValue.second;

  if (lhsChildValue->toString() == rhsChildValue->toString()) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyNegations(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const auto &lhsExpr = cast<IExpression>(lhsChild);
  const auto &rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && is<Neg>(lhsExpr->getFunction()) && is<Neg>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(),
                                  ArgumentsPtrVector{lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});
  }

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().front(), NEG_ONE.clone(), rhsChild});
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), {rhsExpr->getChildren().front(), NEG_ONE.clone(), lhsChild});
  }

  return {};
}

MulExpression::FunctionsVector MulExpression::getFunctionsForSimplify() const {
  return {
      &MulExpression::simplifyNegations, //
      &MulExpression::simplifyDivisions, //
      &MulExpression::mulRates,          //
      &MulExpression::simplifyNumbers,   //
      &MulExpression::mulPolynoms,       //
  };
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

}
