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

CompExpression::CompExpression(const IOperator &oper, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)
    : IBinaryExpressionCRTP(oper, lhsChild, rhsChild) {
}

string CompExpression::toString() const {
  if (isSolution) {
    if (const auto lhsExpr = cast<IExpression>(lhsChild); lhsExpr && *lhsExpr->getFunction() == Add()) {
      ArgumentsPtrVector sumChildren = lhsExpr->getChildren();

      ArgumentPtr solLhs = sumChildren.front();

      if (is<Variable>(solLhs)) {
        sumChildren.erase(sumChildren.begin());

        ArgumentPtr solRhs = makeFunctionExpression(Neg(), {sumChildren});

        if (const auto solRhsExpr = cast<IExpression>(solRhs)) {
          if (solRhsExpr->getVariables().empty()) {
            return CompExpression(cast<IOperator>(*func), solLhs, solRhs).toString();
          }
        }
        else {
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
      return make_shared<CompExpression>(cast<IOperator>(*func), resLhs, ZERO.clone());
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

    bool isAdd = false;
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

    shared_ptr<const INumber> dividerNum;

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

      ArgumentPtr newLhs = makeFunctionExpression(Add(), dividendPolynom); // TODO: add ZERO
      ArgumentPtr newRhs = simplExpr->rhsChild;
      shared_ptr<IFunction> newFunc;

      if (*dividerNum < ZERO) {
        newFunc = getOppositeFunction(func);
      }
      else {
        newFunc = func;
      }

      return makeFunctionExpression(*newFunc, {newLhs, newRhs});
    }
  }

  return simpl;
}

void CompExpression::markAsSolution() {
  isSolution = true;
  convertToSolution();
}

void CompExpression::addOppositeFunctions(const shared_ptr<IFunction> &function,
                                          const shared_ptr<IFunction> &opposite) {
  oppositeFunctionsMap.try_emplace(function->toString(), opposite);
}

shared_ptr<IFunction> CompExpression::getOppositeFunction(const shared_ptr<IFunction> &function) {
  if (auto res = oppositeFunctionsMap.find(function->toString()); res != oppositeFunctionsMap.end()) {
    return cast<IFunction>(res->second->clone());
  }

  return {};
}

void CompExpression::convertToSolution() {
  auto vars = getVariables();

  if (vars.size() != 1) {
    return;
  }

  shared_ptr<const Variable> var = cast<Variable>(vars.front());

  if (auto lhsAddExpr = cast<IExpression>(lhsChild); lhsAddExpr && is<Add>(lhsAddExpr->getFunction())) {
    ArgumentsPtrVector rhsPolynom = {rhsChild};
    ArgumentsPtrVector lhsPolynom = {ZERO.clone()};

    for (const auto &lhsChild : lhsAddExpr->getChildren()) {
      if (const auto lhsChildExpr = cast<IExpression>(lhsChild); lhsChildExpr && hasVariables(lhsChildExpr, var)) {
        lhsPolynom.emplace_back(lhsChild);
      }
      else if (const auto lhsChildVar = cast<Variable>(lhsChild); lhsChildVar && *lhsChildVar == *var) {
        lhsPolynom.emplace_back(lhsChild);
      }
      else {
        rhsPolynom.emplace_back(makeFunctionExpression(Neg(), {lhsChild}));
      }
    }

    lhsChild = makeFunctionExpression(Add(), lhsPolynom);
    rhsChild = makeFunctionExpression(Add(), rhsPolynom);
  }
}

}
