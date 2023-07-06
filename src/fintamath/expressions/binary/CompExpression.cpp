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

        ArgumentPtr solRhs = makeExpr(Neg(), sumChildren);
        simplifyChild(solRhs);

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

  if (!simplExpr->isSolution && (!is<Integer>(rhsChild) || *rhsChild != Integer(0))) {
    ArgumentPtr resLhs = makeExpr(Sub(), simplExpr->lhsChild, simplExpr->rhsChild);
    simplifyChild(resLhs);
    return std::make_shared<CompExpression>(cast<IOperator>(*func), resLhs, std::make_shared<Integer>(0));
  }

  return simplExpr;
}

CompExpression::SimplifyFunctionsVector CompExpression::getFunctionsForPostSimplify() const {
  static const CompExpression::SimplifyFunctionsVector simplifyFunctions = {
      &CompExpression::coeffSimplify, //
  };
  return simplifyFunctions;
}

void CompExpression::markAsSolution() {
  isSolution = true;
}

std::shared_ptr<IFunction> CompExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Eqv().toString(), std::make_shared<Eqv>()},         //
      {Neqv().toString(), std::make_shared<Neqv>()},       //
      {More().toString(), std::make_shared<Less>()},       //
      {Less().toString(), std::make_shared<More>()},       //
      {MoreEqv().toString(), std::make_shared<LessEqv>()}, //
      {LessEqv().toString(), std::make_shared<MoreEqv>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

ArgumentPtr CompExpression::coeffSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto lhsExpr = cast<IExpression>(lhs)) {
    if (is<Neg>(lhsExpr->getFunction())) {
      ArgumentPtr res = makeExpr(*getOppositeFunction(func), lhsExpr->getChildren().front(), rhs);
      simplifyChild(res);
      return res;
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
        dividerNum = cast<INumber>(std::make_shared<Integer>(-1));
      }
      else if (is<Mul>(polynomFirstChildExpr->getFunction())) {
        dividerNum = cast<INumber>(polynomFirstChildExpr->getChildren().front());
      }
    }

    if (dividerNum) {
      for (auto &child : dividendPolynom) {
        child = makeExpr(Div(), child, dividerNum);
      }

      ArgumentPtr newLhs = makeExpr(Add(), dividendPolynom);
      simplifyChild(newLhs);

      if (*dividerNum < Integer(0)) {
        return makeExpr(*cast<IFunction>(getOppositeFunction(func)), newLhs, rhs);
      }

      return makeExpr(func, newLhs, rhs);
    }
  }
  return {};
}

}
