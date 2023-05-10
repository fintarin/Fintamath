#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

CompExpression::CompExpression(const IOperator &inOper, const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(inOper, inLhsChild, inRhsChild) {
}

std::string CompExpression::toString() const {
  if (isSolution) {
    if (const auto lhsExpr = cast<IExpression>(lhsChild); lhsExpr && *lhsExpr->getFunction() == Add()) {
      ArgumentsPtrVector sumChildren = lhsExpr->getChildren();

      ArgumentPtr solLhs = sumChildren.front();

      if (is<Variable>(solLhs)) {
        sumChildren.erase(sumChildren.begin());

        ArgumentPtr solRhs = makeFunctionExpression(Neg(), sumChildren);

        if (!is<IExpression>(solRhs)) {
          return CompExpression(cast<IOperator>(*func), solLhs, solRhs).toString();
        }
      }
    }
  }

  return IBinaryExpression::toString();
}

ArgumentPtr CompExpression::preSimplify() const {
  auto simpl = IBinaryExpression::preSimplify();
  auto simplExpr = cast<CompExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (!simplExpr->isSolution) {
    if (!is<Integer>(rhsChild) || *rhsChild != ZERO) {
      ArgumentPtr resLhs = makeFunctionExpression(Sub(), simplExpr->lhsChild, simplExpr->rhsChild);
      return std::make_shared<CompExpression>(cast<IOperator>(*func), resLhs, ZERO.clone());
    }
  }

  return simplExpr;
}

ArgumentPtr CompExpression::postSimplify() const {
  auto simpl = IBinaryExpression::postSimplify();
  auto simplExpr = cast<CompExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (auto lhsExpr = cast<IExpression>(simplExpr->lhsChild)) {
    if (is<Neg>(lhsExpr->getFunction())) {
      return makeFunctionExpression(*getOppositeFunction(*func), lhsExpr->getChildren().front(), simplExpr->rhsChild);
    }

    ArgumentsPtrVector dividendPolynom;
    ArgumentPtr polynomFirstChild;

    if (is<Add>(lhsExpr->getFunction())) {
      polynomFirstChild = lhsExpr->getChildren().front();
      dividendPolynom = lhsExpr->getChildren();
    }
    else {
      polynomFirstChild = lhsExpr;
      dividendPolynom.emplace_back(lhsExpr);
    }

    std::shared_ptr<const INumber> dividerNum;

    if (const auto polynomFirstChildExpr = cast<IExpression>(polynomFirstChild)) {
      if (is<Neg>(polynomFirstChildExpr->getFunction())) {
        dividerNum = cast<INumber>(NEG_ONE.clone());
      }
      else if (is<Mul>(polynomFirstChildExpr->getFunction())) {
        dividerNum = cast<INumber>(polynomFirstChildExpr->getChildren().front());
      }
    }

    if (dividerNum) {
      for (auto &child : dividendPolynom) {
        child = makeRawFunctionExpression(Div(), child, dividerNum);
      }

      ArgumentPtr newLhs = makeFunctionExpression(Add(), dividendPolynom);
      ArgumentPtr newRhs = simplExpr->rhsChild;
      std::shared_ptr<IFunction> newFunc;

      if (*dividerNum < ZERO) {
        newFunc = cast<IFunction>(getOppositeFunction(*func));
      }
      else {
        newFunc = func;
      }

      return makeRawFunctionExpression(*newFunc, newLhs, newRhs);
    }
  }

  return simpl;
}

ArgumentPtr CompExpression::logicNegate() const {
  auto res = cast<CompExpression>(clone());
  res->func = cast<IFunction>(getLogicOppositeFunction(*func));
  return res;
}

CompExpression::SimplifyFunctionsVector CompExpression::getFunctionsForPreSimplify() const {
  // TODO! implement
  return {};
}

CompExpression::SimplifyFunctionsVector CompExpression::getFunctionsForPostSimplify() const {
  // TODO! implement
  return {};
}

void CompExpression::markAsSolution() {
  isSolution = true;
}

std::shared_ptr<IFunction> CompExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>> oppositeFunctions = {
      {Eqv().toString(), std::make_shared<Eqv>()},         //
      {Neqv().toString(), std::make_shared<Neqv>()},       //
      {More().toString(), std::make_shared<Less>()},       //
      {Less().toString(), std::make_shared<More>()},       //
      {MoreEqv().toString(), std::make_shared<LessEqv>()}, //
      {LessEqv().toString(), std::make_shared<MoreEqv>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

std::shared_ptr<IFunction> CompExpression::getLogicOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>> oppositeFunctions = {
      {Eqv().toString(), std::make_shared<Neqv>()},     //
      {Neqv().toString(), std::make_shared<Eqv>()},     //
      {More().toString(), std::make_shared<LessEqv>()}, //
      {Less().toString(), std::make_shared<MoreEqv>()}, //
      {MoreEqv().toString(), std::make_shared<Less>()}, //
      {LessEqv().toString(), std::make_shared<More>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

}
