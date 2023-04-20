#include "fintamath/expressions/binary/CompExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
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
  if (auto rhsInt = cast<Integer>(simplExpr->rhsChild); (!rhsInt || *rhsInt != ZERO) && !simplExpr->isSolution) {
    ArgumentPtr resLhs = makeFunctionExpression(Sub(), {simplExpr->lhsChild, simplExpr->rhsChild});
    return std::make_shared<CompExpression>(cast<IOperator>(*func), resLhs, ZERO.clone());
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
      return makeFunctionExpression(*getOpposite(func), {lhsExpr->getChildren().front(), simplExpr->rhsChild});
    }

    bool isAdd = false;
    ArgumentsPtrVector polynomForDivision;

    ArgumentPtr firstValue;
    if (is<Add>(lhsExpr->getFunction())) {
      firstValue = lhsExpr->getChildren().front();
      polynomForDivision = lhsExpr->getChildren();
    }
    else {
      firstValue = lhsExpr;
      polynomForDivision.emplace_back(lhsExpr);
    }

    shared_ptr<const INumber> valForDiv;
    if (const auto &valExpr = cast<IExpression>(firstValue)) {
      if (is<Neg>(valExpr->getFunction())) {
        valForDiv = cast<INumber>(NEG_ONE.clone());
      }
      else if (is<Mul>(valExpr->getFunction())) {
        valForDiv = cast<INumber>(valExpr->getChildren().front());
      }
    }

    if (valForDiv) {
      for (auto &child : polynomForDivision) {
        child = makeFunctionExpression(Mul(), {child, makeFunctionExpression(Inv(), {valForDiv->clone()})});
      }

      ArgumentPtr lhsValue = makeFunctionExpression(Add(), polynomForDivision); // TODO: add ZERO

      shared_ptr<IFunction> function;
      if (*valForDiv < ZERO) {
        function = getOpposite(func);
      }
      else {
        function = func;
      }

      return makeFunctionExpression(*function, {lhsValue, simplExpr->rhsChild});
    }
  }

  return simpl;
}

void CompExpression::copyProperties(const CompExpression &rhs) {
  isSolution = rhs.isSolution;
  if (isSolution) {
    convertToSolution();
  }
}

void CompExpression::markAsSolution() {
  isSolution = true;
  convertToSolution();
}

void CompExpression::setOppositeToFunction(const shared_ptr<IFunction> &function,
                                           const shared_ptr<IFunction> &opposite) {
  functionOpposMap.try_emplace(function->toString(), opposite);
}

shared_ptr<IFunction> CompExpression::getOpposite(const shared_ptr<IFunction> &function) {
  return cast<IFunction>(functionOpposMap[function->toString()]->clone());
}

void CompExpression::convertToSolution() {
  auto vars = getVariables();
  if (vars.size() != 1) {
    return;
  }

  shared_ptr<const Variable> var = cast<Variable>(vars.front());

  if (auto lhsAddExpr = cast<IExpression>(lhsChild); lhsAddExpr && is<Add>(lhsAddExpr->getFunction())) {
    ArgumentsPtrVector lhsChildPolynom = lhsAddExpr->getChildren();
    ArgumentsPtrVector rhsPolynom = {rhsChild};
    ArgumentsPtrVector lhsPolynom = {ZERO.clone()};

    for (const auto &child : lhsAddExpr->getChildren()) {
      if (const auto &childExpr = cast<IExpression>(child); childExpr && hasVariable(childExpr, var)) {
        lhsPolynom.emplace_back(child);
        continue;
      }
      if (const auto &childVar = cast<Variable>(child); childVar && *childVar == *var) {
        lhsPolynom.emplace_back(child);
        continue;
      }
      rhsPolynom.emplace_back(makeFunctionExpression(Neg(), {child}));
    }
    lhsChild = makeFunctionExpression(Add(), lhsPolynom);
    rhsChild = makeFunctionExpression(Add(), rhsPolynom);
  }
}

}
