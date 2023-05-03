#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
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

        ArgumentPtr solRhs = makeFunctionExpression(Neg(), {sumChildren});

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
      ArgumentPtr resLhs = makeFunctionExpression(Sub(), {simplExpr->lhsChild, simplExpr->rhsChild});
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
      return makeFunctionExpression(*getOppositeFunction(func), {lhsExpr->getChildren().front(), simplExpr->rhsChild});
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
        child = makeRawFunctionExpression(Div(), {child, dividerNum});
      }

      ArgumentPtr newLhs = makeFunctionExpression(Add(), dividendPolynom);
      ArgumentPtr newRhs = simplExpr->rhsChild;
      std::shared_ptr<IFunction> newFunc;

      if (*dividerNum < ZERO) {
        newFunc = getOppositeFunction(func);
      }
      else {
        newFunc = func;
      }

      return makeRawFunctionExpression(*newFunc, {newLhs, newRhs});
    }
  }

  return simpl;
}

ArgumentPtr CompExpression::logicNegate() const {
  auto res = cast<CompExpression>(clone());
  res->func = getLogicOppositeFunction(func);
  return res;
}

void CompExpression::markAsSolution() {
  isSolution = true;
}

void CompExpression::addOppositeFunctions(const std::shared_ptr<IFunction> &function,
                                          const std::shared_ptr<IFunction> &opposite) {
  oppositeFunctionsMap.try_emplace(function->toString(), opposite);
}

std::shared_ptr<IFunction> CompExpression::getOppositeFunction(const std::shared_ptr<IFunction> &function) {
  return oppositeFunctionsMap[function->toString()];
}

void CompExpression::addLogicOppositeFunctions(const std::shared_ptr<IFunction> &function,
                                               const std::shared_ptr<IFunction> &opposite) {
  logicOppositeFunctionsMap.try_emplace(function->toString(), opposite);
}

std::shared_ptr<IFunction> CompExpression::getLogicOppositeFunction(const std::shared_ptr<IFunction> &function) {
  return logicOppositeFunctionsMap[function->toString()];
}

}
